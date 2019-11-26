import { Controller, Get, Param } from '@nestjs/common';
import { AppService } from './app.service';

@Controller()
export class AppController {
  constructor(private readonly appService: AppService) {}

  @Get('/hello')
  getHello(): string {
    return this.appService.getHello();
  }

  @Get('/md5sum/:num')
  md5sum(@Param("num") num: number): string {
    return this.appService.md5sum(num);
  }
}
