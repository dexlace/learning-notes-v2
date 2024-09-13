package com.dexlace.kafka.consumer;

import org.apache.kafka.clients.consumer.ConsumerRecord;
import org.apache.kafka.clients.consumer.ConsumerRecords;
import org.apache.kafka.clients.consumer.KafkaConsumer;
import org.apache.kafka.clients.consumer.OffsetAndMetadata;
import org.apache.kafka.common.TopicPartition;
import org.apache.kafka.common.errors.WakeupException;

import java.time.Duration;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Properties;
import java.util.concurrent.atomic.AtomicBoolean;

public class ConsumerThreadSample {
    private final static String TOPIC_NAME="judy";

    /*
        这种类型是经典模式，每一个线程单独创建一个KafkaConsumer，用于保证线程安全
     */
    public static void main(String[] args) throws InterruptedException {
        KafkaConsumerRunner r1 = new KafkaConsumerRunner();
        Thread t1 = new Thread(r1);

        t1.start();

        Thread.sleep(15000);

        r1.shutdown();
    }

    public static class KafkaConsumerRunner implements Runnable{
        private final AtomicBoolean closed = new AtomicBoolean(false);
        private final KafkaConsumer consumer;

        public KafkaConsumerRunner() {
            // 配置消费者
            Properties props = new Properties();
            props.put("bootstrap.servers",  "kafka100:9092,kafka101:9092,kafka102:9092");
            props.put("group.id", "thread-test");
            props.put("enable.auto.commit", "false");
            props.put("auto.commit.interval.ms", "1000");
            props.put("session.timeout.ms", "30000");
            props.put("key.deserializer", "org.apache.kafka.common.serialization.StringDeserializer");
            props.put("value.deserializer", "org.apache.kafka.common.serialization.StringDeserializer");

            consumer = new KafkaConsumer<>(props);

            TopicPartition p0 = new TopicPartition(TOPIC_NAME, 0);
            TopicPartition p1 = new TopicPartition(TOPIC_NAME, 1);

            consumer.assign(Arrays.asList(p0,p1));
        }


        public void run() {
            try {
                while(!closed.get()) {
                    //处理消息
                    ConsumerRecords<String, String> records = consumer.poll(10000);

                    for (TopicPartition partition : records.partitions()) {
                        List<ConsumerRecord<String, String>> pRecord = records.records(partition);
                        // 处理每个分区的消息
                        for (ConsumerRecord<String, String> record : pRecord) {
                            System.out.printf("patition = %d , offset = %d, key = %s, value = %s%n",
                                    record.partition(),record.offset(), record.key(), record.value());
                        }

                        // 返回去告诉kafka新的offset
                        long lastOffset = pRecord.get(pRecord.size() - 1).offset();
                        // 注意加1
                        consumer.commitSync(Collections.singletonMap(partition, new OffsetAndMetadata(lastOffset + 1)));
                    }

                }
            }catch(WakeupException e) {
                if(!closed.get()) {
                    throw e;
                }
            }finally {
                consumer.close();
            }
        }

        // 关闭  把开关变量close关掉即可
        public void shutdown() {
            closed.set(true);
            consumer.wakeup();
        }
    }

}
