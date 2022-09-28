package com.example.a201600282hw2

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import org.w3c.dom.Text

class MainActivity : AppCompatActivity() {

    lateinit var id : TextView; lateinit var  pa : TextView
    lateinit var res : TextView; lateinit var  idtext : EditText
    lateinit var patext : EditText; lateinit var btn : Button
    lateinit var string1 : String; lateinit var string2 : String

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        title : "로그인"

        id = findViewById<TextView>(R.id.idText)
        pa = findViewById<TextView>(R.id.passwordText)
        res = findViewById<TextView>(R.id.resulttext)
        idtext = findViewById<EditText>(R.id.idInput)
        patext = findViewById<EditText>(R.id.passwordText)
        btn = findViewById<Button>(R.id.loginButton)

        btn.setOnTouchListener { view, motionevent ->
            string1 = idtext.text.toString()
            string2 = patext.text.toString()
        }
    }
}