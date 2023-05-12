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
    external fun getIntValue(a: Int,b:Int): Int

    external fun testBaseDataValue(a:Char, b:Int, c:Long, e:Float, f: Double, g:Short, h:Byte):String
    external fun testArray(string: String,intArray: IntArray):String
    external fun testJniChanageJavaBean(person: Person)
}