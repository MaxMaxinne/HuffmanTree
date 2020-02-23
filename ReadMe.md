#数据结构课程设计——霍夫曼编码译码器

霍夫曼编码译码器在实现了要求功能（见requirements.txt)的同时，增加了自动权值统计功能，使程序的使用更加方便，更具有实用性，并支持对中文的编码与译码。
##编译
在根目录下打开命令行，make即可

##编/译码器的使用
*file_encode（编码器）

调用file_encode.exe时，如果要手动输入权值，请在命令行中输入./file_encode filename 其中filename为需要编码的文件名，如选择自动统计权值，请在添加--autocount参数，在命令行中输入./file_encode filename --autocount，请注意--autocount跟在filename之后，并以空格隔开。

*file_decode（译码器）
调用file_decode.exe时，无需任何参数，请确保codefile文件与hfmtree文件与file_deocde.exe处于同一文件夹下，打印的霍夫曼编码保存在在codeprint.txt文件中，打印的二叉树保存在treeprint.txt中，请注意，二叉树的非字符节点以“\*”代替，且可能出现不可见字符的情况（中文文件中尤为如此）