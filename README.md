# IRhdus_test
## IR HDUS Test for Arduino Leonardo / Micro / Pro Micro ( ATmega32U4 )

### HDUSのリモコンの受光部だけArduinoのATmega32U4のUSBデバイス機能でキーボードエミュで作ってみるテスト

#### 1st release

配線はこのページを参考に（接続ピンの配置が少し違うけど…
[配線図](https://ae01.alicdn.com/kf/HTB1QTkvNXXXXXbIXpXXq6xXFXXXe/220871072/HTB1QTkvNXXXXXbIXpXXq6xXFXXXe.jpg)

受光モジュールは、 HX1838。

ProMicroのブレッドボードのサンプル画像
上の配線図と違うところは、IRのピンが９pinでLEDのピンを10pinに接続するところ。
![ProMicro配線図](https://i.imgur.com/jP7wmfe.jpg)

動作テストしたところ、HDUSリモコンだけWin10の64ビットで動作することを確認。
