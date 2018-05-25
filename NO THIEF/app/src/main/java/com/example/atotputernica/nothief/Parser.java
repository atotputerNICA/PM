package com.example.atotputernica.nothief;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.app.ProgressDialog;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.ListAdapter;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.Toast;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.HashMap;
public class Parser extends AppCompatActivity {

    TextView t;
    Button ref;
    String url = "https://api.thingspeak.com/channels/503858/feeds.json";
    ArrayList<HashMap<String, String>> contactList;
    String str="";

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.results);
        t = (TextView) findViewById(R.id.text_view_id);
        ref = (Button) findViewById(R.id.refresh);
        new GetContacts().execute();
        ref.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                str="";
                new GetContacts().execute();
            }
        });
    }



    /**
     * Async task class to get json by making HTTP call
     */
    private class GetContacts extends AsyncTask<Void, Void, Void> {

        @Override
        protected void onPreExecute() {
            super.onPreExecute();
            // Showing progress dialog

        }

        @Override
        protected Void doInBackground(Void... arg0) {
            HttpHandler sh = new HttpHandler();

            // Making a request to url and getting response
            String jsonStr = sh.makeServiceCall(url);

            Log.e("Parser", "Response from url: " + jsonStr);

            if (jsonStr != null) {
                try {

                    JSONObject jsonObj = new JSONObject(jsonStr);
                    Log.i("parser", jsonObj.toString());

//                    // Getting JSON Array node
                    JSONArray feeds = jsonObj.getJSONArray("feeds");
//
//                    // looping through All Contacts
                    Log.i("feeds", feeds.toString() + feeds.length());
                    for (int i = 0; i < feeds.length(); i++) {
                        JSONObject f = feeds.getJSONObject(i);

//                        JSONObject c = contacts.getJSONObject(i);
//
                        String id = f.getString("created_at");
                        str += id + ":";
                       // Log.i("id", str);
                       String name = f.getString("field3");
                       // Log.i("name", name);
                        //Log.i("str", str);
                        if (name.equals("3")) {
                           str += "ALARM TRIGGERED\n";
                       } else {
                           str += "SOMEONE IN! CORRECT PASSWORD\n";
                       }
                        Log.i("str", str);

                    }

                } catch (final JSONException e) {
                    Log.e("Parser", "Json parsing error: " + e.getMessage());
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            Toast.makeText(getApplicationContext(),
                                    "Json parsing error: " + e.getMessage(),
                                    Toast.LENGTH_LONG)
                                    .show();
                        }
                    });

                }
            } else {
                Log.e("Parser", "Couldn't get json from server.");
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        Toast.makeText(getApplicationContext(),
                                "Couldn't get json from server. Check LogCat for possible errors!",
                                Toast.LENGTH_LONG)
                                .show();
                    }
                });

            }

            return null;
        }

        @Override
        protected void onPostExecute(Void result) {
            super.onPostExecute(result);
            t.setText(str);
//            ListAdapter adapter = new SimpleAdapter(
//                    Parser.this, contactList,
//                    R.layout.list_item, new String[]{"name", "email",
//                    "mobile"}, new int[]{R.id.name,
//                    R.id.email, R.id.mobile});
//
//            lv.setAdapter(adapter);
        }

    }
}






  