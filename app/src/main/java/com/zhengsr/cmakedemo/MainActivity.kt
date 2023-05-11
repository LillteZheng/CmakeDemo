package com.zhengsr.cmakedemo

import android.content.Context
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.LinearLayoutManager
import com.chad.library.adapter.base.BaseQuickAdapter
import com.chad.library.adapter.base.viewholder.BaseViewHolder
import com.zhengsr.cmakedemo.databinding.ActivityMainBinding
import com.zhengsr.cmakedemo.lesson.BaseLesson
import com.zhengsr.cmakedemo.lesson.Lesson_1
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    private var curRender: BaseLesson? = null
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        setContentView(R.layout.activity_main)


        val data = arrayListOf<RenderItem>(
            RenderItem(Lesson_1::class.java, "L1 - 加载so库"),

            )
        with(recycleView) {
            layoutManager = LinearLayoutManager(this@MainActivity)
            val testAdapter = TestAdapter(data)
            testAdapter.setOnItemClickListener { adapter, view, position ->
                curRender = getRenderer(data[position].className)?.apply {
                    showUI(this@MainActivity)
                    recycleView.visibility = View.GONE
                    rootContent.addView(this.view)
                }


            }
            adapter = testAdapter

        }

    }

    override fun onBackPressed() {

        if (recycleView.visibility == View.GONE) {
            recycleView.visibility = View.VISIBLE
            curRender?.dismiss()
            return
        }
        super.onBackPressed()
    }

    class TestAdapter(datas:ArrayList<RenderItem>) : BaseQuickAdapter<RenderItem, BaseViewHolder>(R.layout.layout_item,datas) {

        override fun convert(holder: BaseViewHolder, item: RenderItem) {
            // 设置item数据
            item?.let {
                holder.setText(R.id.item_text, it.content)
            }
        }

    }


    data class RenderItem(val className: Class<*>, val content: String)

    fun getRenderer(className: Class<*>): BaseLesson? {
        try {
            val constructor = className.getConstructor()
            return constructor.newInstance() as BaseLesson
        } catch (e: Exception) {
            e.printStackTrace()
        }
        return null
    }
}