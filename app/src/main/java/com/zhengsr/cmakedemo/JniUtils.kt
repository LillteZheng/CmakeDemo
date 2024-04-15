package com.zhengsr.cmakedemo

/**
 * @author by zhengshaorui 2023/5/10
 * describe：
 */
object JniUtils {
    init {
        System.loadLibrary("jniUtils")
        System.loadLibrary("myTest")
    }

    external fun getTestName(): String
    external fun getIntValue(a: Int, b: Int): Int

    external fun testBaseDataValue(
        a: Char,
        b: Int,
        c: Long,
        e: Float,
        f: Double,
        g: Short,
        h: Byte
    ): String

    external fun testArray(string: String, intArray: IntArray): String
    external fun testJniChanageJavaBean(person: Person)
    external fun testJniJavaMethod(person: Person): String
    external fun testThrowError(a: Int, b: Int): Int
    external fun getStringFromC(): String
    external fun getIntFromC(a: Int, b: Int,c:Int): Int

    external fun timerTask(listener: OnTimerListener)

    interface OnTimerListener{
        fun onTimer(count : Int)
    }
}