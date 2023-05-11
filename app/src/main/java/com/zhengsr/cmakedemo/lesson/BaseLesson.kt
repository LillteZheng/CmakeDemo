package com.zhengsr.cmakedemo.lesson

import android.content.Context
import android.opengl.GLSurfaceView
import android.view.View

/**
 * @author by zhengshaorui 2023/5/10
 * describe：
 */
abstract class BaseLesson {
    var view: View? = null
    protected lateinit var context: Context
    fun showUI(context: Context){
        this.context = context
        show(context)
    }


    protected open fun show(context: Context)  {
    }
    open fun dismiss(){
        view?.visibility = View.GONE
    }
}