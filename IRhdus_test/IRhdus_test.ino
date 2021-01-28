// IR HDUS Test for Arduino Leonardo / Micro / Pro Micro
//  by 2020 LVhJPic0JSk5LiQ1ITskKVk9UGBg
#include <IRremote.h>
#include "Keyboard.h"

const int RECV_PIN = 9;    // IR Signal digital input pin#
const int ACTIVE_PIN = 10; // Active LED digital output pin#

IRrecv irrecv(RECV_PIN);

decode_results results;

using milli_t = decltype(millis()) ;

milli_t last_pressed = 0 ;
const milli_t release_wait = 120 ;
const milli_t idle_delay = 10 ;

bool ircode_kx(decltype(decode_results::value) ircode)
{
  char k=0 ; // Key code
  bool c=false,s=false ; // Modifier [Ctrl/Shift]
  switch(ircode) { // Identify the ir code is valid or not
    case 0x50EF01FE:    //画面表示
      s=true; k=KEY_F13; break;

    case 0x50EF817E:    //POWER
      s=true; k=KEY_F14; break;

    case 0x50EF41BE:    //消音
      s=true; k=KEY_F15; break;

    case 0x50EF8976:    //1
      s=true; k=KEY_F17; break;

    case 0x50EF49B6:    //2
      s=true; k=KEY_F18; break;

    case 0x50EFC936:    //3
      s=true; k=KEY_F19; break;

    case 0x50EF29D6:    //4
      s=true; k=KEY_F20; break;

    case 0x50EFA956:    //5
      s=true; k=KEY_F21; break;

    case 0x50EF6996:    //6
      s=true; k=KEY_F22; break;

    case 0x50EFE916:    //7
      s=true; k=KEY_F23; break;

    case 0x50EF19E6:    //8
      s=true; k=KEY_F24; break;

    case 0x50EF9966:    //9
      c=true; k=KEY_F13; break;

    case 0x50EF09F6:    //10
      s=true; k=KEY_F16; break;

    case 0x50EF03FC:    //11
      c=true; k=KEY_F14; break;

    case 0x50EF837C:    //12
      c=true; k=KEY_F15; break;

    case 0x50EFC13E:    //音量+
      s=true; k=KEY_UP_ARROW; break;

    case 0x50EF21DE:    //音量-
      s=true; k=KEY_DOWN_ARROW; break;

    case 0x50EFA15E:    //チャンネル+
      c=true; k=KEY_UP_ARROW; break;

    case 0x50EF619E:    //チャンネル-
      c=true; k=KEY_DOWN_ARROW; break;

    case 0x50EF43BC:    //メニュー
      c=true; k=KEY_F16; break;

    case 0x50EFC33C:    //全画面表示
      c=true; k=KEY_F17; break;

    case 0x50EF23DC:    //字幕
      c=true; k=KEY_F18; break;

    case 0x50EFA35C:    //音声切替
      c=true; k=KEY_F19; break;

    case 0x50EFE31C:    //上
      k=KEY_UP_ARROW; break;

    case 0x50EF936C:    //下
      k=KEY_DOWN_ARROW; break;

    case 0x50EF639C:    //左
      k=KEY_LEFT_ARROW; break;

    case 0x50EF13EC:    //右
      k=KEY_RIGHT_ARROW; break;

    case 0x50EF53AC:    //決定
      k=KEY_RETURN; break;

    case 0x50EFD32C:    //EPG
      c=true; k=KEY_F20; break;

    case 0x50EF33CC:    //戻る
      c=true; k=KEY_F21; break;

    case 0x50EFB34C:    //録画
      c=true; k=KEY_F22; break;

    case 0x50EF738C:    //メモ
      c=true; k=KEY_F23; break;

    case 0x50EF0BF4:    //停止
      c=true; k=KEY_F24; break;

    case 0x50EF8B74:    //再生
      c=s=true; k=KEY_F13; break;

    case 0x50EF4BB4:    //一時停止
      c=s=true; k=KEY_F14; break;

    case 0x50EFCB34:    //｜＜＜
      c=s=true; k=KEY_F15; break;

    case 0x50EF2BD4:    //＜＜
      c=s=true; k=KEY_F16; break;

    case 0x50EFAB54:    //＞＞
      c=s=true; k=KEY_F17; break;

    case 0x50EF6B94:    //＞＞｜
      c=s=true; k=KEY_F18; break;

    case 0x50EFEB14:    //しおり
      c=s=true; k=KEY_F19; break;

    case 0x50EF1BE4:    //ジャンプ
      c=s=true; k=KEY_F20; break;

    case 0x50EF5BA4:    //青
      c=s=true; k=KEY_F21; break;

    case 0x50EFDB24:    //赤
      c=s=true; k=KEY_F22; break;

    case 0x50EF3BC4:    //緑
      c=s=true; k=KEY_F23; break;

    case 0x50EFBB44:    //黄
      c=s=true; k=KEY_F24; break;

  }
  if(k) { // Valid ir code
    // Simulate a keyboard event
    if(c) Keyboard.press(KEY_LEFT_CTRL) ;
    if(s) Keyboard.press(KEY_LEFT_SHIFT) ;
    Keyboard.press(k) ;
    return true ;
  }
  // Invalid ir code
  return false ;
}

void setup()
{
  pinMode(ACTIVE_PIN,OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("HDUS receiver started.");
}

void loop()
{
  auto dur=[](milli_t s=0, milli_t e=millis()) -> decltype(e-s) {
      // duration ( s -> e )
      return s <= e ? e - s : ~s + 1 + e;
  };

  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    if( (last_pressed&&results.value==0xFFFFFFFFUL) ||
        ircode_kx(results.value) ) {
      last_pressed = dur() ;
      digitalWrite(ACTIVE_PIN,HIGH) ;
    }
    irrecv.resume(); // Receive the next value
  }else {
    if(last_pressed>0) {
      if(dur(last_pressed)>=release_wait) {
        Keyboard.releaseAll();
        digitalWrite(ACTIVE_PIN,LOW) ;
        last_pressed=0 ;
      }
    }else
      delay(idle_delay) ;
  }
}