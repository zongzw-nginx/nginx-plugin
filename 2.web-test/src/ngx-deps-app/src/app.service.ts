import { Injectable } from '@nestjs/common';

@Injectable()
export class AppService {
  getHello(): string {
    return 'Hello World!';
  }

  md5sum(num: number): string {
    let c = require("crypto");
    let md5f = (d: string): string => {
      return c.createHash('md5').update(d).digest('hex');
    }

    let st = new Date().getTime(); 
    let fin = '';
    let ns = '';
    for(let n=0; n<num; n+=1) {
      ns = `${n}`;
      fin = md5f(ns);
    }
    let dt = new Date().getTime(); 

    let dur = dt - st;
    // console.log(`${fin}: ${ns}, tv:${dur} millisecs`);

    return `${fin}: ${ns}, tv:${dur} millisecs`;
  }
}
