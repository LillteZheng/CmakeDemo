package com.zhengsr.cmakedemo

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import androidx.recyclerview.widget.LinearLayoutManager
import com.chad.library.adapter.base.BaseQuickAdapter
import com.chad.library.adapter.base.viewholder.BaseViewHolder
import com.zhengsr.cmakedemo.lesson.BaseLesson
import com.zhengsr.cmakedemo.lesson.Lesson_1
import com.zhengsr.cmakedemo.lesson.Lesson_2
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    private var curRender: BaseLesson? = null
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        setContentView(R.layout.activity_main)


        val data = arrayListOf<LessonItem>(
            LessonItem(Lesson_1::class.java, "L1 - 加载so库"),
            LessonItem(Lesson_2::class.java, "L2 - 数据类型传递"),

            )
        with(recycleView) {
            layoutManager = LinearLayoutManager(this@MainActivity)
            val testAdapter = TestAdapter(data)
            testAdapter.setOnItemClickListener { adapter, view, position ->
                curRender = getRenderer(data[position].className)?.apply {
                    showInnerView(this@MainActivity)
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

    class TestAdapter(datas:ArrayList<LessonItem>) : BaseQuickAdapter<LessonItem, BaseViewHolder>(R.layout.layout_item,datas) {

        override fun convert(holder: BaseViewHolder, item: LessonItem) {
            // 设置item数据
            item?.let {
                holder.setText(R.id.item_text, it.content)
            }
        }

    }


    data class LessonItem(val className: Class<*>, val content: String)

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