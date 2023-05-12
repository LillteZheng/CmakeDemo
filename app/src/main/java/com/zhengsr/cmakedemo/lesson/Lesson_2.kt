package com.zhengsr.cmakedemo.lesson

import android.content.Context
import android.graphics.Color
import android.util.TypedValue
import android.view.Gravity
import android.view.ViewGroup
import android.widget.FrameLayout
import android.widget.LinearLayout
import android.widget.TextView
import com.zhengsr.cmakedemo.JniUtils
import com.zhengsr.cmakedemo.Person

/**
 * @author by zhengshaorui 2023/5/10
 * describe：
 */
class Lesson_2 : BaseLesson() {
    override fun show(context: Context) = run {
        FrameLayout(context).also { frame ->
            frame.layoutParams = ViewGroup.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.MATCH_PARENT
            )
            val textView = TextView(context).apply {
                layoutParams = ViewGroup.LayoutParams(
                    ViewGroup.LayoutParams.MATCH_PARENT,
                    ViewGroup.LayoutParams.MATCH_PARENT
                )
                setTextColor(Color.BLACK)
                setTextSize(TypedValue.COMPLEX_UNIT_SP, 20f)
                text = "请点击左侧按钮，验证问题"
                gravity = Gravity.CENTER

            }
            LinearLayout(context).apply {
                layoutParams = ViewGroup.LayoutParams(
                    ViewGroup.LayoutParams.WRAP_CONTENT,
                    ViewGroup.LayoutParams.WRAP_CONTENT
                )
                orientation = LinearLayout.VERTICAL
                addBtn("基本数据") {
                    val msg = JniUtils.testBaseDataValue('a',1,2L,3f,4.0,5,"6".toByte())
                    textView.text = msg
                }
                addBtn("引用数据：String，数组"){
                    val msg = JniUtils.testArray("hello world", intArrayOf(1,2,3,4,5))
                    textView.text = msg
                }
                addBtn("Jni修改Java类"){
                    val person = Person("李四",21)
                    val old = "修改之前:$person"
                    JniUtils.testJniChanageJavaBean(person)
                    val new = "\tJni修改后:$person"
                    textView.text = "$old $new"
                }
                frame.addView(this)
            }
            frame.addView(textView)

        }
    }

}