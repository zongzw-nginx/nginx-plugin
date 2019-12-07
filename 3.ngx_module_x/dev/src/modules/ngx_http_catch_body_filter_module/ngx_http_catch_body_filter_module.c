
/*
 * Copyright (C) Maxim Dounin
 */

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>


typedef struct {
    ngx_flag_t         enable;
} ngx_http_catch_body_conf_t;


static void *ngx_http_catch_body_create_conf(ngx_conf_t *cf);
static char *ngx_http_catch_body_merge_conf(ngx_conf_t *cf, void *parent,
    void *child);
static ngx_int_t ngx_http_catch_body_init(ngx_conf_t *cf);


static ngx_command_t  ngx_http_catch_body_commands[] = {

    { ngx_string("catch_body"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_FLAG,
      ngx_conf_set_flag_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_catch_body_conf_t, enable),
      NULL },

      ngx_null_command
};


static ngx_http_module_t  ngx_http_catch_body_module_ctx = {
    NULL,                          /* preconfiguration */
    ngx_http_catch_body_init,      /* postconfiguration */

    NULL,                          /* create main configuration */
    NULL,                          /* init main configuration */

    NULL,                          /* create server configuration */
    NULL,                          /* merge server configuration */

    ngx_http_catch_body_create_conf, /* create location configuration */
    ngx_http_catch_body_merge_conf   /* merge location configuration */
};


ngx_module_t  ngx_http_catch_body_filter_module = {
    NGX_MODULE_V1,
    &ngx_http_catch_body_module_ctx, /* module context */
    ngx_http_catch_body_commands,  /* module directives */
    NGX_HTTP_MODULE,               /* module type */
    NULL,                          /* init master */
    NULL,                          /* init module */
    NULL,                          /* init process */
    NULL,                          /* init thread */
    NULL,                          /* exit thread */
    NULL,                          /* exit process */
    NULL,                          /* exit master */
    NGX_MODULE_V1_PADDING
};


static ngx_http_request_body_filter_pt   ngx_http_next_request_body_filter;


static ngx_int_t
ngx_http_catch_body_filter(ngx_http_request_t *r, ngx_chain_t *in)
{
    u_char                      *p;
    ngx_chain_t                 *cl;
    ngx_http_catch_body_conf_t  *conf;

    conf = ngx_http_get_module_loc_conf(r, ngx_http_catch_body_filter_module);

    if (!conf->enable) {
        return ngx_http_next_request_body_filter(r, in);
    }

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "catch request body filter");

    for (cl = in; cl; cl = cl->next) {

        p = cl->buf->pos;

        for (p = cl->buf->pos; p < cl->buf->last; p++) {

            ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "catch body in:%02Xd:%c", *p, *p);

            if (*p == 'X') {
                ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                               "catch body: found");

                /*
                 * As we return NGX_HTTP_FORBIDDEN, the r->keepalive flag
                 * won't be reset by ngx_http_special_response_handler().
                 * Make sure to reset it to prevent processing of unread
                 * parts of the request body.
                 */

                r->keepalive = 0;

                return NGX_HTTP_FORBIDDEN;
            }
        }
    }

    return ngx_http_next_request_body_filter(r, in);
}


static void *
ngx_http_catch_body_create_conf(ngx_conf_t *cf)
{
    ngx_http_catch_body_conf_t  *conf;

    conf = ngx_pcalloc(cf->pool, sizeof(ngx_http_catch_body_conf_t));
    if (conf == NULL) {
        return NULL;
    }

    conf->enable = NGX_CONF_UNSET;

    return conf;
}


static char *
ngx_http_catch_body_merge_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_catch_body_conf_t *prev = parent;
    ngx_http_catch_body_conf_t *conf = child;

    ngx_conf_merge_value(conf->enable, prev->enable, 0);

    return NGX_CONF_OK;
}


static ngx_int_t
ngx_http_catch_body_init(ngx_conf_t *cf)
{
    ngx_http_next_request_body_filter = ngx_http_top_request_body_filter;
    ngx_http_top_request_body_filter = ngx_http_catch_body_filter;

    return NGX_OK;
}
