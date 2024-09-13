package com.dexlace.consumer;

import org.springframework.amqp.rabbit.annotation.Queue;
import org.springframework.amqp.rabbit.annotation.RabbitHandler;
import org.springframework.amqp.rabbit.annotation.RabbitListener;
import org.springframework.stereotype.Component;


/**
 * @Author: xiaogongbing
 * @Description:
 * @Date: 2021/3/19
 */
//@Component
// 没有队列则创建队列
// @Queue可以设置持久化  是否自动删除
@RabbitListener(queuesToDeclare = @Queue("hello"))
public class HelloConsumer {


    @RabbitHandler
    public void recieve(String message){
        System.out.println("message= " + message);
    }



}
