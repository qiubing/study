#include <linux/init.h>     /* __init __exit*/
#include <linux/modules.h>  /* module_init */
#include <linux/kernel.h>   /*printk()*/

#define DEBUG   //open debug message  
  
#ifdef DEBUG  
#define PRINTK(fmt, arg...)     printk(KERN_WARNING fmt, ##arg)  
#else  
#define PRINTK(fmt, arg...)     printk(KERN_DEBUG fmt, ##arg)  
#endif  


static int __init hello_init(void)    /*模块加载函数，通过insmod命令加载模块时，被自行执行 */
{
	printk(KERN_INFO "Hello World enter\n");
	return 0;
}

static void __exit hello_exit(void) /*模块卸载函数，当通过rmmod命令卸载时，会自动执行*/
{
	printk(KERN_INFO "Hello World exit\n");
	return;

}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("qiubing"); /*模块作者，可选*/
MODULE_LICENSE("Dual BSD/GPL"); /* 模块许可证明，描述内核模块的许可权限，必须*/

MODULE_DESCRIPTION("A simple Hello World Module"); /*模块说明，可选*/


