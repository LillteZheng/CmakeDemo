package com.zhengsr.cmakedemo.lesson

import android.content.Context
import android.opengl.GLSurfaceView
import android.view.View
import android.view.ViewGroup
import android.widget.Button

/**
 * @author by zhengshaorui 2023/5/10
 * describe：
 */
abstract class BaseLesson {
    var view: View? = null
    protected lateinit var context: Context
    fun showInnerView(context: Context){
        this.context = context
        if (view == null) {
            view =  show(context)
            view?.parent?.let {
                (it as ViewGroup).removeView(view)
            }
        }
        view?.visibility = View.VISIBLE
    }


    protected abstract fun show(context: Context) :View?

    open fun dismiss(){
        view?.visibility = View.GONE
    }

    fun ViewGroup.addBtn(msg:String, block:()->Unit){
        Button(context).apply {
            layoutParams = ViewGroup.LayoutParams(
                ViewGroup.LayoutParams.WRAP_CONTENT,
                ViewGroup.LayoutParams.WRAP_CONTENT
            )
            text = msg
            setOnClickListener {
                block.invoke()
            }
            addView(this)
        }
    }
}