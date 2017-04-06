package com.example.yuusuke.huistenbosch;

import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.DialogInterface.OnCancelListener;
import android.os.AsyncTask;
import android.util.Log;

import jcifs.smb.SmbFile;
import jcifs.smb.SmbFileOutputStream;

public class Main4Activity//toccoの操作支援機能
        extends AsyncTask<Object, Object, Long>

        implements OnCancelListener {
    final String TAG = "MyAsyncTask";
    ProgressDialog dialog;
    Context context;

    public Main4Activity(Context context) {
        this.context = context;
    }

    @Override
    protected void onPreExecute() {
        Log.d(TAG, "onPreExecute");
        dialog = new ProgressDialog(context);
        dialog.setTitle("Please wait");
        dialog.setMessage("Loading data...");
        dialog.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);
        dialog.setCancelable(true);
        dialog.setOnCancelListener(this);
        dialog.setMax(100);
        dialog.setProgress(0);
        dialog.show();


    }


    @Override
    protected Long doInBackground(Object... params) {
        Log.d(TAG, "doInBackground - " + params[0]);

        try {
            SmbFile file = new SmbFile("smb://192.168.10.123/Release/"); /*繋ぎたいパソコンのユーザー名、パスワード、ドメイン、フォルダーパス*/
            String[] filenames = file.list();
            for (int i = 0; i < filenames.length; i++) {
                System.out.println(filenames[i]);/*中のファイルを表示*/

            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        try {
            for (int i = 0; i < 10; i++) {
                if (isCancelled()) {
                    Log.d(TAG, "Cancelled!");
                    break;
                }
                Thread.sleep(10);
                publishProgress((i + 1) * 10);
            }
        } catch (InterruptedException e) {
            Log.d(TAG, "InterruptedException in doInBackground");
        }



        System.out.println("START2");//csvファイルに０を上書きする
        String data1 = "1";/*ここにファイル内容を記載する*///片足立ち左
        SmbFileOutputStream fos1 = null;
        try {
            SmbFile file = new SmbFile("smb://192.168.10.123/Release/start.csv");    /*("smb://192.168.2.104/秀和システム/squatstartapuri.csv");/*ここにsmb://ユーザー名:パスワード@アドレス/フォルダ名/ファイル名*/
            if (!file.exists()) {
                file.createNewFile();
            }
            fos1 = new SmbFileOutputStream(file);
            fos1.write(data1.getBytes());
            fos1.close();
        } catch (Exception e) {
            e.printStackTrace();
            System.err.println("ERR");
        } finally {
            if (fos1 != null) {
                try {
                    fos1.close();
                } catch (Exception e) {
                }
            }




            return 123L;

        }}

    @Override
    protected void onProgressUpdate(Object... values) {
        Log.d(TAG, "onProgressUpdate - " + values[0]);
        dialog.setProgress((Integer) values[0]);
    }

    @Override
    protected void onCancelled() {
        Log.d(TAG, "onCancelled");
        dialog.dismiss();
    }

    @Override
    protected void onPostExecute(Long result) {
        Log.d(TAG, "onPostExecute - " + result);
        dialog.dismiss();
    }

    @Override
    public void onCancel(DialogInterface dialog) {
        Log.d(TAG, "Dialog onCancell... calling cancel(true)");
        this.cancel(true);
    }}

