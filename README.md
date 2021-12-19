# IRhdus_test
IR HDUS Test for Arduino Leonardo / Micro / Pro Micro ( ATmega32U4 )

## HDUSのリモコンの受光部だけArduinoのATmega32U4のUSBデバイス機能のキーボードエミュで作ってみるテスト

### [3rd release revised](../../releases/tag/3rd_rev)

  - サスペンドから復帰時、誤動作防止の為、サスペンド状態の判定に遊びを持たせる工程を追加

### [3rd release](../../releases/tag/3rd)

  - サスペンドからの復帰時に自己リセットして修復させる機能を追加

  と、その写真と配線図。
  ![3rd写真](https://i.imgur.com/bC9SBAB.jpg)

  ![3rd配線図](https://i.imgur.com/hqSY334.gif)

  緑枠の部分を組み上げるとレジューム時に自己リセット機能が働くようになる(実装しなくても動作可)。
  リセットボタンはProMicroだとスケッチアップロードに失敗した場合などに2回連打すると8秒間だけLeonardoに偽装できるのであると便利。


### [2nd release](../../releases/tag/2nd)

  - サスペンド中のPCをHDUSリモコンの電源ボタン押下で復帰させる機能を追加

  と、おまけの配線図。
  ![おまけの配線図](https://i.imgur.com/tsA220E.gif)


  ※HX1838のリモコンと一緒に販売されている基板実装されているものは、端子の配置が異なるので要注意。
  ![HX1838ピンアサイン](https://i.imgur.com/dunMcHS.jpg)


### [1st release](../../releases/tag/1st)

  配線は[このページ](https://ae01.alicdn.com/kf/HTB1QTkvNXXXXXbIXpXXq6xXFXXXe/220871072/HTB1QTkvNXXXXXbIXpXXq6xXFXXXe.jpg)を参考に（接続ピンの配置が少し違うけど…

  受光モジュールは、 HX1838。

  ProMicroのブレッドボードのサンプル画像。
  上の配線図と違うところは、IRのピンが９pinでLEDのピンを10pinに接続するところ。
  ![ProMicro配線図](https://i.imgur.com/MqJ6tsV.jpg)

  動作テストしたところ、HDUSリモコンだけWin10の64ビットで動作することを確認。
