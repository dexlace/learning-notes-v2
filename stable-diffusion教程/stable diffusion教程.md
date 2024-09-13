# stable diffusion教程

## 一、提示词

人物或主体特征：服饰穿搭，发型发色，五官特点，面部表情，肢体动作；

场景特征：室内室外，大场景，小细节；

环境光照：白天黑夜，特定时段，光环境，填空

画幅视角：距离，人物比例，观察视角，镜头类型；

画质提示词：高画质，分辨率

画风提示词：插画风，二次元，写实系

提示词网站：`ai.dawnmark.cn`

`((提示词))`:加一层括号权重乘1.1倍

`(提示词:1.2)`：1.2也是权重

类推`{}`为1.05,`[]`为0.9

## 二、checkpoint、VAE和微调模型

主模型：checkpoint和VAE模型

注意checkpoint文件放到modle的stable diffusion文件夹下

`RuntimeError: "upsample_nearest2d_channels_last" not implemented for 'Half'`:

解决办法：在启动的时候 ./webui.sh --no-half，把半精度禁止掉，就可以正常使用了。这个是因为mac支持不了这种优化

微调模型：

- `Embeddings`指的是嵌入式向量，词嵌入，相当于标签，下载之后放在`models\Embeddings`文件夹下，文件和VAE一样，是.pt结尾的，图生图中可以反推提示词

- `Lora`大语言模型的低阶适应，这是微软的研究人员为了解决大语言模型微调而开发的一项技术，下载之后放在`models\Lora`文件夹下，在提示词中使用`<Lora:lora模型名:权重>`，或者在generate按钮下的的几个小按钮中可以加额外的网络，选择Lora即可

- `Hypernetwork` 它和 LoRA 很类似，它是让梯度作用于模型的扩散 (Diffusion) 过程。扩散过程中的每一步都通过一个额外的小网络来调整去噪过程的结果。这个模型主要用于画风。

### 三、文生图、图生图、高清修复、局部重绘



## 四、ControlNet

