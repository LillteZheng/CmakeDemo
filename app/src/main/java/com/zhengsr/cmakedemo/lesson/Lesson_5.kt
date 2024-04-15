package com.zhengsr.cmakedemo.lesson

import android.content.Context
import android.graphics.Color
import android.util.Log
import android.util.TypedValue
import android.view.Gravity
import android.view.ViewGroup
import android.widget.FrameLayout
import android.widget.LinearLayout
import android.widget.TextView
import com.zhengsr.cmakedemo.JniUtils
import com.zhengsr.cmakedemo.Person
import kotlin.concurrent.thread

/**
 * @author by zhengshaorui 2023/5/10
 * describe：
 */
class Lesson_5 : BaseLesson() {
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

                addBtn("创建 pthread_create,监听变化") {
                    JniUtils.testJniThread(object : JniUtils.OnTimerListener {
                        override fun onTimer(count: Int) {
                            textView.post {
                                textView.text = "当前数值：$count"
                            }
                        }
                    })

                }

                frame.addView(this)
            }
            frame.addView(textView)

        }
    }

}