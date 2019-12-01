// extern "C" {
#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <ngx_md5.h>
// }

#include <stdlib.h>
// #include <openssl/md5.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>


typedef struct {
    ngx_str_t output_words;
} ngx_http_my_md5_loc_conf_t;
 
// To process HelloWorld command arguments
static char* ngx_http_my_md5(ngx_conf_t* cf, ngx_command_t* cmd, void* conf);
 
// Allocate memory for HelloWorld command
static void* ngx_http_my_md5_create_loc_conf(ngx_conf_t* cf);
 
// Copy HelloWorld argument to another place
static char* ngx_http_my_md5_merge_loc_conf(ngx_conf_t* cf, void* parent, void* child);
 
#ifndef MD5_DIGEST_LENGTH
#define MD5_DIGEST_LENGTH 16
#endif

#define MD5_STRING_LENGTH MD5_DIGEST_LENGTH * 2

ngx_int_t md5_str(ngx_md5_t* ctx, char* str, char* rlt) {
    unsigned char ch16[MD5_DIGEST_LENGTH];
    memset(ch16, 0, MD5_DIGEST_LENGTH);

    ngx_md5_init(ctx);
    ngx_md5_update(ctx, str, strlen(str));
    ngx_md5_final(ch16, ctx);

    for (int nIndex = 0; nIndex < MD5_DIGEST_LENGTH; nIndex++)
    {
        sprintf(rlt + nIndex * 2, "%02x", ch16[nIndex]);
    }

    return NGX_OK;
}

int run_md5_n_times_with_timer(ngx_md5_t* ctx, int num, ngx_str_t* output)
{
        int st, et, stu, etu; 
        struct timeval tv;

        char ch32[MD5_STRING_LENGTH + 1];
        memset(ch32, 0, MD5_STRING_LENGTH + 1);

        char ns[16];
        memset(ns, 0, 16);

        gettimeofday(&tv, NULL);
        st = tv.tv_sec;
        stu = tv.tv_usec;
        int i = 0;
        while (i < num)
        {
                sprintf(ns, "%d", i);
                md5_str(ctx, ns, ch32);
                i++;
        }

        gettimeofday(&tv, NULL);
        et = tv.tv_sec;
        etu = tv.tv_usec;

        char tmp[256];
        ngx_memset(tmp, 0, 256);
        sprintf(tmp, "%s: %s, tv:%d millisecs", ch32, ns, (et-st)*1000 + (etu - stu)/1000);
        ngx_sprintf(output->data, "%s", tmp);
        output->len = ngx_strlen(output->data);

        return NGX_OK;
}

// Structure for the HelloWorld command
static ngx_command_t ngx_http_my_md5_commands[] = {
    {
        ngx_string("md5_from_1_to"), // The command name
        NGX_HTTP_LOC_CONF | NGX_CONF_TAKE1,
        ngx_http_my_md5, // The command handler
        NGX_HTTP_LOC_CONF_OFFSET,
        offsetof(ngx_http_my_md5_loc_conf_t, output_words),
        NULL
    },
    ngx_null_command
};
 
// Structure for the HelloWorld context
static ngx_http_module_t ngx_http_my_md5_module_ctx = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ngx_http_my_md5_create_loc_conf,
    ngx_http_my_md5_merge_loc_conf
};
 
// Structure for the HelloWorld module, the most important thing
ngx_module_t ngx_http_my_md5_module = {
    NGX_MODULE_V1,
    &ngx_http_my_md5_module_ctx,
    ngx_http_my_md5_commands,
    NGX_HTTP_MODULE,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NGX_MODULE_V1_PADDING
};
 
static ngx_int_t ngx_http_my_md5_handler(ngx_http_request_t* r) {
    ngx_int_t rc;
    ngx_buf_t* b;
    ngx_chain_t out;
 
    ngx_http_my_md5_loc_conf_t* hlcf;
    hlcf = (ngx_http_my_md5_loc_conf_t*)ngx_http_get_module_loc_conf(r, ngx_http_my_md5_module);
 
    r->headers_out.content_type.len = sizeof("text/plain") - 1;
    r->headers_out.content_type.data = (u_char*)"text/plain";
 
    b = (ngx_buf_t*)ngx_pcalloc(r->pool, sizeof(ngx_buf_t));
 
    out.buf = b;
    out.next = NULL;
 
    ngx_md5_t *ctx = (ngx_md5_t*)ngx_pcalloc(r->pool, sizeof(ngx_md5_t));
    ngx_str_t *rltstr = (ngx_str_t*)ngx_pcalloc(r->pool, sizeof(ngx_str_t));
    rltstr->data = (u_char*)ngx_pcalloc(r->pool, 256);

    int num = atoi((const char*)(hlcf->output_words.data));
    run_md5_n_times_with_timer(ctx, num, rltstr); 

    b->pos = (u_char*)rltstr->data;
    b->last = b->pos + rltstr->len;
    b->memory = 1;
    b->last_buf = 1;
 
    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_length_n = rltstr->len;
    rc = ngx_http_send_header(r);
    if (rc == NGX_ERROR || rc > NGX_OK || r->header_only) {
        return rc;
    }
 
    return ngx_http_output_filter(r, &out);
}
 
static void* ngx_http_my_md5_create_loc_conf(ngx_conf_t* cf) {
    ngx_http_my_md5_loc_conf_t* conf;
 
    conf = (ngx_http_my_md5_loc_conf_t*)ngx_pcalloc(cf->pool, sizeof(ngx_http_my_md5_loc_conf_t));
    if (conf == NULL) {
        return NGX_CONF_ERROR;
    }
    conf->output_words.len = 0;
    conf->output_words.data = NULL;
 
    return conf;
}
 
static char* ngx_http_my_md5_merge_loc_conf(ngx_conf_t* cf, void* parent, void* child) {
    ngx_http_my_md5_loc_conf_t* prev = (ngx_http_my_md5_loc_conf_t*)parent;
    ngx_http_my_md5_loc_conf_t* conf = (ngx_http_my_md5_loc_conf_t*)child;
    ngx_conf_merge_str_value(conf->output_words, prev->output_words, "Nginx");
    return NGX_CONF_OK;
}
 
static char* ngx_http_my_md5(ngx_conf_t* cf, ngx_command_t* cmd, void* conf) {
    ngx_http_core_loc_conf_t* clcf;
    clcf = (ngx_http_core_loc_conf_t*)ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_my_md5_handler;
    ngx_conf_set_str_slot(cf, cmd, conf);
    return NGX_CONF_OK;
}
