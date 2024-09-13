package com.dexlace.confirm;



import org.springframework.amqp.core.*;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class MQConfiguration {
    //队列名称
    public static final String QUEUQ_NAME = "xiangjiao.queue";
    //交换器名称
    public static final String EXCHANGE = "xiangjiao.exchange";
    //路由key
    public static final String ROUTING_KEY = "xiangjiao.routingKey";

    //创建队列
    @Bean
    public Queue getQueue(){
        // 另一种方式
        //QueueBuilder.durable(QUEUQ_NAME).build();
        return new Queue(QUEUQ_NAME);
    }
    //实例化交换机
    @Bean
    public DirectExchange getDirectExchange(){
        //DirectExchange(String name, boolean durable, boolean autoDelete)

        // 另一种方式：
        //ExchangeBuilder.directExchange(EXCHANGE).durable(true).build();
        /**
         * 参数一：交换机名称；<br>
         * 参数二：是否永久；<br>
         * 参数三：是否自动删除；<br>
         */
        return new DirectExchange(EXCHANGE, true, false);
    }
    //绑定消息队列和交换机
    @Bean
    public Binding bindExchangeAndQueue(DirectExchange exchange,Queue queue){
        // 将 创建的 queue 和 exchange 进行绑定
        return BindingBuilder.bind(queue).to(exchange).with(ROUTING_KEY);
    }
}
