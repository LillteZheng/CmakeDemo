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
                    val msg = JniUtils.testBaseDataValue('a',1,2L,"你好",3f,4.0,5,"6".toByte())
                    textView.text = msg
                }
                frame.addView(this)
            }
            frame.addView(textView)

        }
    }

}