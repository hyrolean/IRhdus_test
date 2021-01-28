// IR HDUS Test for Arduino Leonardo / Micro / Pro Micro ( ATmega32U4 )
//  2nd released by 2020 LVhJPic0JSk5LiQ1ITskKVk9UGBg
//   - Fixed the USB recover failing problem when resuming a suspended PC.
//   - Added the feature to wakeup a suspended PC by pressing the POWER button.
//  1st released @ https://pastebin.com/1zycyEMD
#include <IRremote.h>
#include "Keyboard.h"

#define SUPPORT_WAKEUP_HOST 1 // Feature to wakeup a suspended PC [0/1]

const int RECV_PIN = 9;    // IR Signal digital input pin#
const int ACTIVE_PIN = 10; // Active LED digital output pin#

IRrecv irrecv(RECV_PIN);

using msec_t = decltype(millis()) ;
using ircode_t = decltype(decode_results::value) ;

msec_t last_pressed = 0 ;
const msec_t RELEASE_WAIT = 120 ;
const msec_t IDLE_DELAY = 10 ;
const msec_t SUSPENDED_DELAY = 500 ;
const msec_t RESUME_DELAY = 1000 ;

const ircode_t REPEAT_CODE = 0xFFFFFFFFUL ;

bool suspended=true ;

bool ircode_kx(ircode_t ircode)
{
  unsigned char k=0 ; // Key code
  bool c=false,s=false ; // Modifier [Ctrl/Shift]
  bool p=false ; // POWER pressed
  switch(ircode) { // Identify the ir code is valid or not
    case 0x50EF01FE:    //画面表示
      s=true; k=KEY_F13; break;

    case 0x50EF817E:    //POWER
      s=p=true; k=KEY_F14; break;

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
    if(suspended) {
      #if SUPPORT_WAKEUP_HOST
      // Wakeup a supended PC
      if(p) USBDevice.wakeupHost();
      #endif
      return false ;
    }else {
      // Emulate a keyboard event
      if(c) Keyboard.press(KEY_LEFT_CTRL) ;
      if(s) Keyboard.press(KEY_LEFT_SHIFT) ;
      Keyboard.press(k) ;
    }
    return true ;
  }
  // Invalid ir code
  return false ;
}

void setup()
{
  pinMode(ACTIVE_PIN,OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
}

void loop()
{
  auto dur=[](msec_t s=0, msec_t e=millis()) -> decltype(e-s) {
      // duration ( s -> e )
      return s <= e ? e - s : ~s + 1 + e;
  };

  static decode_results results;

  if(USBDevice.isSuspended()) {
    if(!suspended) {
      Keyboard.end() ;
      Serial.end() ;
      #if !SUPPORT_WAKEUP_HOST
      USBDevice.detach();
      #endif
      suspended=true ;
    }
  }else if(suspended) {
    digitalWrite(ACTIVE_PIN,HIGH) ;
    delay(RESUME_DELAY) ;
    #if !SUPPORT_WAKEUP_HOST
    USBDevice.attach();
    #endif
    Serial.begin(9600);
    Serial.println("HDUS receiver resumed.");
    Keyboard.begin() ;
    suspended=false ;
    digitalWrite(ACTIVE_PIN,LOW) ;
  }

  if (irrecv.decode(&results)) {
    if(!suspended) Serial.println(results.value, HEX);
    if( (last_pressed&&results.value==REPEAT_CODE) ||
        ircode_kx(results.value) ) {
      last_pressed = dur() ;
      digitalWrite(ACTIVE_PIN,HIGH) ;
    }
    irrecv.resume(); // Receive the next value
  }else {
    if(last_pressed) {
      if(dur(last_pressed)>=RELEASE_WAIT) {
        if(!suspended) Keyboard.releaseAll();
        digitalWrite(ACTIVE_PIN,LOW) ;
        last_pressed=0 ;
      }
    }else
      delay(suspended?SUSPENDED_DELAY:IDLE_DELAY) ;
  }
}