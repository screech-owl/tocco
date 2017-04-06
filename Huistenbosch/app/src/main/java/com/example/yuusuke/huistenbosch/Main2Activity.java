package com.example.yuusuke.huistenbosch;

import android.app.Activity;
import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.speech.RecognizerIntent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.Toast;

import java.util.ArrayList;

import static com.example.yuusuke.huistenbosch.R.id.button2;
import static com.example.yuusuke.huistenbosch.R.id.button3;
import static com.example.yuusuke.huistenbosch.R.id.button5;
import static com.example.yuusuke.huistenbosch.R.id.button6;


public class Main2Activity extends Activity
        implements OnClickListener {
    final String TAG = "AsyncTest";
    // = 0 の部分は、適当な値に変更してください（とりあえず試すには問題ないですが）
    private static final int REQUEST_CODE = 0;
    // 再生の準備
    MediaPlayer p;


    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);
        Button button1 = (Button) findViewById(R.id.button2);
        button1.setOnClickListener(this);
        Button button2 = (Button) findViewById(R.id.button3);
        button2.setOnClickListener(this);
        Button button3 = (Button) findViewById(R.id.button5);
        button3.setOnClickListener(this);Button
                button4 = (Button) findViewById(R.id.button6);
        button4.setOnClickListener(this);

        ImageButton button5 = (ImageButton) findViewById(R.id.imageButton);
        button5.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Sub 画面を起動
                Intent intent = new Intent();
                intent.setClassName("com.example.yuusuke.huistenbosch", "com.example.yuusuke.huistenbosch.MainActivity");
                startActivity(intent);
            }

        });




        Button button = (Button) findViewById(R.id.button);

        button.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                try {
                    // インテント作成
                    Intent intent = new Intent(
                            RecognizerIntent.ACTION_RECOGNIZE_SPEECH); // ACTION_WEB_SEARCH
                    intent.putExtra(
                            RecognizerIntent.EXTRA_LANGUAGE_MODEL,
                            RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
                    intent.putExtra(
                            RecognizerIntent.EXTRA_PROMPT,
                            "とっこに話しかけてみて！！"); // お好きな文字に変更できます

                    // インテント発行
                    startActivityForResult(intent, REQUEST_CODE);

                } catch (ActivityNotFoundException e) {
                    // このインテントに応答できるアクティビティがインストールされていない場合
                    Toast.makeText(Main2Activity.this,
                            "ActivityNotFoundException", Toast.LENGTH_LONG).show();
                }
            }
        });

    }


    // アクティビティ終了時に呼び出される
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        // 自分が投げたインテントであれば応答する
        if (requestCode == REQUEST_CODE && resultCode == RESULT_OK) {
            String resultsString = "";

            // 結果文字列リスト
            ArrayList<String> results = data.getStringArrayListExtra(
                    RecognizerIntent.EXTRA_RESULTS);

            for (int i = 0; i < results.size(); i++) {
                // ここでは、文字列が複数あった場合に結合しています
                resultsString += results.get(i);
            }
            String aisatsu = new String("こんにちは");//ここでキーワードを設定
            String baka = new String("ばか");
            String baibai = new String("ばいばい");
            String tyantokiiteru = new String("ちゃんときいてる");
            String kaigan = new String("片足立ち");
            String squat = new String("スクワット");
            String daisuki = new String("大好き");
            String tukareta = new String("疲れた");
            String hello = new String("名前");
            String tundere = new String("嫌い");
            String tanoshii = new String("楽しい");
            String enaninani = new String("とっこちゃん");
            String kantan = new String("簡単");
            String kawaii = new String("かわいい");
            String hugday = new String("火曜日");
            String nigehazi = new String("パンダ");
            String ending = new String("逃げはじ");
            String waseda = new String("わせだ");




            if (resultsString.indexOf(aisatsu) != -1) {                //キーワードに部分一致しているか判定
                // 音楽の読み込み
                p = MediaPlayer.create(getApplicationContext(), R.raw.aisatsu);//メディアプレーヤーから対応した音声の呼出し
                p.start(); // 再生
            } else if (resultsString.indexOf(baka) != -1) {
                // 音楽の読み込み
                p = MediaPlayer.create(getApplicationContext(), R.raw.kotobapanda);
                p.start(); // 再生

            } else if (resultsString.indexOf(baibai) != -1) {
                // 音楽の読み込み
                p = MediaPlayer.create(getApplicationContext(), R.raw.baibaimatane);
                p.start(); // 再生

            } else if (resultsString.indexOf(tanoshii) != -1) {
                // 音楽の読み込み
                p = MediaPlayer.create(getApplicationContext(), R.raw.hontotanosii);
                p.start(); // 再生

            } else if (resultsString.indexOf(tundere) != -1) {
                // 音楽の読み込み
                p = MediaPlayer.create(getApplicationContext(), R.raw.hontohasuki);
                p.start(); // 再生

            } else if (resultsString.indexOf(tyantokiiteru) != -1) {
                // 音楽の読み込み
                p = MediaPlayer.create(getApplicationContext(), R.raw.bikkuri);
                p.start(); // 再生

            } else if (resultsString.indexOf(hello) != -1) {
                // 音楽の読み込み
                p = MediaPlayer.create(getApplicationContext(), R.raw.hellomynametocco);
                p.start(); // 再生

            } else if (resultsString.indexOf(daisuki) != -1) {
                // 音楽の読み込み
                p = MediaPlayer.create(getApplicationContext(), R.raw.daisuki);
                p.start(); // 再生

            } else if (resultsString.indexOf(tukareta) != -1) {
                // 音楽の読み込み
                p = MediaPlayer.create(getApplicationContext(), R.raw.ganbatterusyouko);
                p.start(); // 再生

            } else if (resultsString.indexOf(enaninani) != -1) {
                // 音楽の読み込み
                p = MediaPlayer.create(getApplicationContext(), R.raw.enaninani);
                p.start(); // 再生

            } else if (resultsString.indexOf(kantan) != -1) {
                // 音楽の読み込み
                p = MediaPlayer.create(getApplicationContext(), R.raw.igaitoturakunaidesyo);
                p.start(); // 再生

            } else if (resultsString.indexOf(kawaii) != -1) {
                // 音楽の読み込み
                p = MediaPlayer.create(getApplicationContext(), R.raw.kimimokawaii);
                p.start(); // 再生

            } else if (resultsString.indexOf(hugday) != -1) {
                // 音楽の読み込み
                p = MediaPlayer.create(getApplicationContext(), R.raw.hugday);
                p.start(); // 再生

            } else if (resultsString.indexOf(nigehazi) != -1) {
                // 音楽の読み込み
                p = MediaPlayer.create(getApplicationContext(), R.raw.nigehazi1);
                p.start(); // 再生

            } else if (resultsString.indexOf(ending) != -1) {
                // 音楽の読み込み
                p = MediaPlayer.create(getApplicationContext(), R.raw.nigehazi2);
                p.start(); // 再生

            } else if (resultsString.indexOf(waseda) != -1) {
                // 音楽の読み込み
                p = MediaPlayer.create(getApplicationContext(), R.raw.kabeken1);
                p.start(); // 再生

            } else if (resultsString.indexOf(kaigan) != -1) {
                // 音楽の読み込み
                p = MediaPlayer.create(getApplicationContext(), R.raw.kaiganmoyattemiyou);
                p.start(); // 再生
                new Main3Activity(this).execute("Param1");//ここでパソコン側のcsv書き換え処理を呼び出している

            } else if (resultsString.indexOf(squat) != -1) {
                //スクワットの音声が必要
                new Main4Activity(this).execute("Param1");

            }else {
                String wrong = "キーワードが違います";
                Toast.makeText(this, wrong, Toast.LENGTH_LONG).show();
                return;
            }


        }
//resultStringが認識結果なのでここから対応する言葉をifで判定音声を発話する


        super.onActivityResult(requestCode, resultCode, data);
    }


    @Override
    public void onClick(View v) {
        if (v.getId() == button2) {
            new Main3Activity(this).execute("Param1");
        }
        if (v.getId() == button3) {
            new Main4Activity(this).execute("Param2");
        }
        if (v.getId() == button5) {
            new Main5Activity(this).execute("Param2");
        }
        if (v.getId() == button6) {
            new Main6Activity(this).execute("Param2");
        }

    }
}




