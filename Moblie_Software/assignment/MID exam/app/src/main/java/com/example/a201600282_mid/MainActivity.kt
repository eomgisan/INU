package com.example.a201600282_mid

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.*
import java.lang.StringBuilder

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        var text : TextView
        var rdbtn1 : RadioButton
        var rdbtn2 : RadioButton
        var rdbtn3 : RadioButton
        var rdbtn4 : RadioButton
        var rdbtn5 : RadioButton
        var rdGroup : RadioGroup
        var editText1 : EditText
        var editText2 : EditText
        var editText3 : EditText
        var btn : Button
        var pee = Array<Int>(3,{0})
        pee[0]=8000
        pee[1]=5000
        pee[2]=10000
        var time = StringBuilder() ; var totalpee = StringBuilder() ; var num = StringBuilder()
        var empty : String = ""

        rdbtn1 = findViewById<RadioButton>(R.id.rbtn1)
        rdbtn2 = findViewById<RadioButton>(R.id.rbtn2)
        rdbtn3 = findViewById<RadioButton>(R.id.rbtn3)
        rdbtn4 = findViewById<RadioButton>(R.id.rbtn4)
        rdbtn5 = findViewById<RadioButton>(R.id.rbtn5)
        text = findViewById<TextView>(R.id.text6)
        rdGroup = findViewById<RadioGroup>(R.id.rdGroup)
        editText1 = findViewById<EditText>(R.id.edit1)
        editText2 = findViewById<EditText>(R.id.edit2)
        editText3 = findViewById<EditText>(R.id.edit3)
        btn = findViewById<Button>(R.id.btn)

        rdbtn1.setText(R.string.time1)
        rdbtn2.setText(R.string.time2)
        rdbtn3.setText(R.string.time3)
        rdbtn4.setText(R.string.time4)
        rdbtn5.setText(R.string.time5)



        btn.setOnClickListener {
            var num1 : String = editText1.text.toString()
            var num2 : String = editText2.text.toString()
            var num3 : String = editText3.text.toString()


            var Num1 : Int = Integer.parseInt(num1)
            var Num2 : Int = Integer.parseInt(num2)
            var Num3 : Int = Integer.parseInt(num3)
            var Num : Int = Num1 + Num2 + Num3

            var totalPee : Int = Num1*pee[0] + Num2*pee[1] + Num3*pee[2]


            if((Num1>10)||(Num2>10)||(Num3>10)||(Num == 0 && Num == 0 && Num == 0)){
                text.text = ""
            }
            else{

                when(rdGroup.checkedRadioButtonId){
                    R.id.rbtn1 -> time.append(rdbtn1.text.toString())
                    R.id.rbtn2 -> time.append(rdbtn2.text.toString())
                    R.id.rbtn3 -> time.append(rdbtn3.text.toString())
                    R.id.rbtn4 -> time.append(rdbtn4.text.toString())
                    R.id.rbtn5 -> time.append(rdbtn5.text.toString())
                }
                num.append(Num.toString())

                totalpee.append(totalPee.toString())

                text.text = "영화 시간 = " + time + " 예매 인원 = " + num + " 총 금액 = " + totalpee

                time.replace(0,10,empty)
                num.replace(0,10,empty)
                totalpee.replace(0,10,empty)
            }



        }

    }

}