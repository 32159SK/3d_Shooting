# 3d_Shooting
3Dゲーム用サンプル

# 内容
* サンプルプロジェクトシューティング
* クレジット.txt
* README.md

# 制作環境
* 開発言語
  * C++
* ライブラリ
  * aqua(学校配布の独自ライブラリ)
* OS
  * Windows 10
* IDE
  * Visual Studio 2019
* 制作期間
  * 4年次前期制作
  * 5ヶ月
* 制作人数
  * 1人(個人製作)
    
# 作品紹介
* C++を用いて制作した3Dゲーム
* 初めてC++で3Dゲームを制作するにあたって、複雑なモデルやモーションを扱うのは困難と思い、簡素なモデルを使用しても違和感のない見下ろし型のシューティングゲームが良いと考えて制作した作品。
* キーボードで移動、マウスで射撃と弾種切り替え、さらに向きを変えられる簡単な操作となっています。また、UIからは基本的に文字を出さないように徹底し、画面の情報量を減らしました。この為、直感的に操作できるシューティングゲームに仕上げることが出来ました。
  
# アピールポイント
 * 学校配布ライブラリに処理追加
 * レイキャスト処理
 * 行列の活用
 * オールレンジ攻撃
 * チュートリアル

## 学校配布ライブラリに処理追加
* 学校配布のライブラリの「aqua」内に三次元空間の処理を行えるクラスがなかった為以下を追加
  * [三次元ベクトルクラス(vector3)](サンプルプロジェクトシューティング/aqua/src/mathematics/vector/vector3)
    * 三次元空間のベクトル・座標処理クラス
  * [行列計算クラス(matrix)](サンプルプロジェクトシューティング/aqua/src/mathematics/matrix)
    * 三次元空間における回転処理等に使用する行列の計算処理クラス
  * [カメラクラス(camera)](サンプルプロジェクトシューティング/aqua/src/graphics/camera)
    * 三次元空間のオブジェクトを描画するために必須のカメラクラス 
  * [各三次元図形描画クラス](サンプルプロジェクトシューティング/aqua/src/graphics/primitive)
    * 主に当たり判定のコリジョンとして活用
      
## レイキャスト処理
* マウス操作で向きを変える際に使用。
  
https://github.com/32159SK/3d_Shooting/assets/101731704/8b983a5b-02a1-44b3-b659-04e893239b75
* 画面上のマウス座標からレイを飛ばし、床モデルと接触した座標を追う事でズレなくマウスの追従
* 処理記載場所
  *  [床クラス(floor.cpp)内：RayCast関数](サンプルプロジェクトシューティング/game/src/game/game_object/floor/floor.cpp)
    
## 行列の活用
* ビームの当たり判定用のカプセルの終点を行列で計算し、決められた長さと向き通り照射させる処理
  *  [ビームクラス(beam.cpp)内：Initialize関数](サンプルプロジェクトシューティング/game/src/game/game_object/bullet_manager/beam/beam.cpp)
 
![beam](https://github.com/32159SK/3d_Shooting/assets/101731704/5d01b8c1-fe35-4763-b3b4-45429d7e0ae9)

    
* ボスの周囲を回る砲エネミーの座標計算も同様の処理で求めている
  
https://github.com/32159SK/3d_Shooting/assets/101731704/32401abd-1d3d-4c41-ad6a-8770228dee9c

* 処理記載場所
  *  [ボスエネミークラス(boss_enemy.cpp)内：SetCannonPosition関数](サンプルプロジェクトシューティング/game/src/game/game_object/enemy_manager/enemy/boss_enemy/boss_enemy.cpp)

## オールレンジ攻撃
* シューティングゲームといえばボスはいるべきと思い、ボス作ると決めた時点で特にやりたかったボスの特殊行動
* ボスの周囲を回転している砲エネミーが自機を囲うように展開してビームを放つ

https://github.com/32159SK/3d_Shooting/assets/101731704/7db28147-3fc0-4938-8f5e-5293a733f4ed

* 処理記載場所
  *  [ボスエネミークラス(boss_enemy.cpp)内：SetCannonPosition関数](サンプルプロジェクトシューティング/game/src/game/game_object/enemy_manager/enemy/boss_enemy/boss_enemy.cpp)
  *  [ボスキャノンエネミークラス(boss_cannon.cpp)内：<br></br>SetAllRange関数・AllRangeMove関数・EasingMove関数・Irradiation関数・ReturnPosition関数](サンプルプロジェクトシューティング/game/src/game/game_object/enemy_manager/enemy/boss_enemy/boss_cannon/boss_cannon.cpp)

## チュートリアル
* 操作方法を確認するためのチュートリアルシーン
* ゲーム内で説明があった方がプレイする人に親切と考え実装しました

https://github.com/32159SK/3d_Shooting/assets/101731704/4007c82d-55b5-4530-9b81-89600d6923e6

* 処理記載場所
  *   [チュートリアルシーンクラス(tutorial)](サンプルプロジェクトシューティング/game/src/game/game_object/scene_manager/scene/tutorial)
  *   [チュートリアルメッセージ描画クラス(tutorial_message)](サンプルプロジェクトシューティング/game/src/game/game_object/ui_component/tutorial_message)
