# ML_Brushless_STM32F030

STM32F030で、ブラシレスモーターを制御するサンプルです。  

詳しい解説はAPS-WEB様に掲載頂いています。  

このREADMEは補足説明です。



# 接続図
[test.pdf](https://github.com/miha-labs/ML_Brushless_STM32F030/files/12002344/test.pdf)

![image](https://github.com/miha-labs/ML_Brushless_STM32F030/assets/95220539/83e71ac5-a6e7-4eb5-9672-2d6e28647f59)


# PC用アプリ
"ML_monitor.exe"  

![画面説明](https://github.com/miha-labs/ML_Brushless_STM32F030/assets/95220539/0ff92693-8873-4435-ad91-1a29c4921e47)  

(1) COMポートの選択とOpen/Close。MCUボードのVCPを選択する。

(2) 回転速度のモニタリングStart/Stop。モーターを手で回しても回転数モニターが可能。

(3) モーター駆動ON/OFFと回転速度指示。駆動をONにしてから回転速度を上げても良いし、回転速度を決めてから駆動をONにしても良い。

(4) 回転速度指示を±100[rpm]ずつ上下する。"0"ボタンで回転速度指示が0[rpm]となる。

(5) 回転速度指示のスライダ。スライダで回転速度指示を行っても良い。大体右のグラフのSpeed[rpm]と同じスケール。

(6) グラフの青線スケール(回転速度)。

(7) グラフの赤線スケール(電流)。


- グラフ表示について  
[ScottPlot](https://scottplot.net/)を使用させて頂きました。  
VisualStudio標準のプロッタより軽量で使いやすいのでおススメです。

# 免責事項
[MITライセンス](https://github.com/miha-labs/ML_Brushless_STM32F030/blob/main/LICENSE)に従います。  
[ScottPlot](https://github.com/ScottPlot/ScottPlot/blob/main/LICENSE)：Copyright (c) 2018 Scott Harden / Harden Technologies, LLC

