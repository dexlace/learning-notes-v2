package com.dexlace.test;

import com.dexlace.RabbitmqSpringbootApplication;
import com.dexlace.confirm.MQConfiguration;
import com.dexlace.confirm.RabbitmqService;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

@SpringBootTest(classes = RabbitmqSpringbootApplication.class)
@RunWith(SpringRunner.class)
public class TestMQConfirm {
    @Autowired
    private RabbitmqService rabbitmqService;

    @Test
    public void testConfirm(){

        //发送10条消息
        for (int i = 0; i < 10; i++) {
            String msg = "msg"+i;
            System.err.println("发送消息  msg："+msg);
            // xiangjiao.exchange  交换机
            // xiangjiao.routingKey  队列
//            rabbitmqService.sendMessage(MQConfiguration.EXCHANGE, MQConfiguration.ROUTING_KEY, msg);
            rabbitmqService.sendMessage("不存在的交换机", MQConfiguration.ROUTING_KEY, msg);
            //每两秒发送一次
            try {
                Thread.sleep(2000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

    }
}
