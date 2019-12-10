# 人のゴミ捨て動作に反応し，映像に変化を与えるRTCコンポーネント群

## 概要
　我々はゴミ箱にディスプレイを取り付け，人がゴミを捨てるとそれに反応して映像が変化するゴミ箱を制作した．映像は物理エンジンで作り，入れたゴミをタピオカに変換して落ちてくるようなものにした．

## 開発環境
 - OS: Windows 10                        
 - RTミドルウェア: OpenRTM-aist 1.2.0-RELESE (C++版) 
 - 開発環境: Visual Studio Community 2017      
 - CMake: CMake 3.14.0                      
 - Python: Python 3.7.2                      
 
## ハードウェア
| 部品名     | 型番         | 個数　　 |
|:-----------|------------:|:------------:|
| 距離センサー | GP2Y0A21 |    1    |
| Arduino     |   UNO |   1   |

## 開発コンポーネント
- [distance](https://github.com/ShibauraRTM/Interactive_Tapioca_GarbageCan/tree/master/distance): 距離が変化したことを検出する．

- [music](https://github.com/ShibauraRTM/Interactive_Tapioca_GarbageCan/tree/master/Music): タピオカが液体に落ちる音を出力する．DXライブラリを用いている．

- [CreateTapioca](https://github.com/ShibauraRTM/Interactive_Tapioca_GarbageCan/tree/master/CreateTapioca): ディスプレイ上でタピオカの映像を表示する．物理エンジン『BulletPhysics』を用いている．

## マニュアル
- 環境構築の方法および本RTCの使用方法については[こちら](https://github.com/ShibauraRTM/Interactive_Tapioca_GarbageCan/blob/master/user_manual.pdf)

## 問い合わせ先
芝浦工業大学付属高等学校
3年生　久保田 浩平
mail: tacotanx@gmail.com
