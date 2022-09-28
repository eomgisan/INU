package com.example.app3

import android.app.Activity
import android.content.Intent
import android.os.Bundle
import android.widget.Button

class SecondActivity : Activity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.second)
        title = "Second 액티비티"

        var inIntent = intent
        var hapValue = inIntent.getIntExtra("Num1",0) + inIntent.getIntExtra("Num2",0)

            var btnReturn = findViewById<Button>(R.id.btnReturn)
            btnReturn.setOnClickListener {
            var outIntent = Intent(applicationContext, MainActivity::class.java)
            outIntent.putExtra("Hap",hapValue)
            setResult(Activity.RESULT_OK, outIntent)
            finish()
        }
    }
}