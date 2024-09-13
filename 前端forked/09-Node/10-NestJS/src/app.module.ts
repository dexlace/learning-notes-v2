import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { VideoModule } from './video/video.module';
import { UserModule } from './user/user.module';

@Module({
  imports: [VideoModule, UserModule],
  controllers: [AppController],
  providers: [AppService],
})
export class AppModule { }
