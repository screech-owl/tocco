package com.example.yuusuke.huistenbosch;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button button6 = (Button) findViewById(R.id.button4);
        button6.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                // Sub 画面を起動
                Intent intent = new Intent();
                intent.setClassName("com.example.yuusuke.huistenbosch", "com.example.yuusuke.huistenbosch.Main2Activity");
                startActivity(intent);
            }


        });
    }
}
