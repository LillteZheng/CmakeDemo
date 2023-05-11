package com.zhengsr.cmakedemo.lesson

import android.content.Context
import android.graphics.Color
import android.util.TypedValue
import android.view.Gravity
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import com.zhengsr.cmakedemo.JniUtils

/**
 * @author by zhengshaorui 2023/5/10
 * describe：
 */
class Lesson_1 :BaseLesson() {
    override fun show(context: Context) {
        super.show(context)
        view = TextView(context).apply {
            layoutParams = ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,ViewGroup.LayoutParams.MATCH_PARENT)
            setTextColor(Color.BLACK)
            setTextSize(TypedValue.COMPLEX_UNIT_SP,24f)
            text = "两数之和: ${JniUtils.getIntValue(10,10)}"
            gravity = Gravity.CENTER
            visibility = View.VISIBLE
        }
    }
}