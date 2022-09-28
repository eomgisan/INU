package com.example.app2

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import androidx.fragment.app.Fragment
import androidx.fragment.app.FragmentActivity

class MainActivity : FragmentActivity() {

    private var fr : Fragment = fragmentA()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val view = findViewById<View>(R.id.fragment_container)
        if (view !=null){
            if(savedInstanceState != null)
                return

            val transaction = supportFragmentManager.beginTransaction()
            transaction.add(R.id.fragment_container, fr)
            transaction.commit()
        }
    }

    fun selectFragement(view: View) {
        fr = fragmentA()
        if (view.id == R.id.btn2){
            fr = fragmentB()
        }

        supportFragmentManager.beginTransaction()
            .replace(R.id.fragment_container, fr)
            .addToBackStack(null)
            .commit()
    }
}
