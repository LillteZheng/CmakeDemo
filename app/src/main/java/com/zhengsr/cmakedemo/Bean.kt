package com.zhengsr.cmakedemo

/**
 * @author by zhengshaorui 2023/5/12
 * describe：
 */
data class Person(val name: String, val age: Int){
    fun getMsg(isCall:Boolean) = if (isCall)("$name age is $age") else "nothing"
}