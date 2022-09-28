package com.example.a201600282hw1

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.EditText
import android.widget.RadioButton
import android.widget.RadioGroup
import android.widget.TextView
import java.lang.ArithmeticException

class MainActivity : AppCompatActivity() {

    lateinit var edit1 : EditText; lateinit var edit2 : EditText
    lateinit var text4 : TextView; lateinit var text1 : TextView
    lateinit var text2 : TextView; lateinit var text3 : TextView
    lateinit var rGroup : RadioGroup; lateinit var rBtn1 : RadioButton
    lateinit var rBtn2 : RadioButton; lateinit var rBtn3 : RadioButton
    lateinit var rBtn4 : RadioButton; var result : Double? = null
    lateinit var num1 : String; lateinit var num2 : String

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        title = "간단한 계산기"

        edit1 = findViewById<EditText>(R.id.Edit1)
        edit2 = findViewById<EditText>(R.id.Edit2)
        text4 = findViewById<EditText>(R.id.Num4)
        rBtn1 = findViewById<RadioButton>(R.id.Rbotton1)
        rBtn2 = findViewById<RadioButton>(R.id.Rbotton2)
        rBtn3 = findViewById<RadioButton>(R.id.Rbotton3)
        rBtn4 = findViewById<RadioButton>(R.id.Rbotton4)
        rGroup = findViewById<RadioGroup>(R.id.Rgroup)
        text1 = findViewById<TextView>(R.id.Num1)
        text2 = findViewById<TextView>(R.id.Num2)
        text3 = findViewById<TextView>(R.id.Num3)



        rBtn1.setOnClickListener {
            when (rGroup.checkedRadioButtonId) {
                R.id.Rbotton1 -> {
                    num1 = edit1.text.toString()
                    num2 = edit2.text.toString()
                    result = Double.valueOf(num1) + Double.valueOf(num2);
                    text4.text = result.toString()
                    false
                }
                R.id.Rbotton2 -> {
                    num1 = edit1.text.toString()
                    num2 = edit2.text.toString()
                    result = Double.valueOf(num1) - Double.valueOf(num2);
                    text4.text = result.toString()
                    false
                }
                R.id.Rbotton3 -> {
                    num1 = edit1.text.toString()
                    num2 = edit2.text.toString()
                    try {
                        result = Double.valueOf(num1) / Double.valueOf(num2);
                    } catch (e:ArithmeticException){
                        text4.text = "계산에 문제가 있습니다."
                    }
                    text4.text = result.toString()
                    false
                }
                R.id.Rbotton4 -> {
                    num1 = edit1.text.toString()
                    num2 = edit2.text.toString()
                    result = Double.valueOf(num1) * Double.valueOf(num2);
                    text4.text = result.toString()
                    false
                }


            }
        }

    }
}