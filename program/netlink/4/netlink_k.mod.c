#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x93f12be5, "module_layout" },
	{ 0xe42b5286, "sock_release" },
	{ 0xb1d9523e, "wait_for_completion_timeout" },
	{ 0x68dfc59f, "__init_waitqueue_head" },
	{ 0x7edbf8c2, "netlink_kernel_create" },
	{ 0x95f3164e, "init_net" },
	{ 0x7c47328c, "netlink_broadcast" },
	{ 0x50eedeb8, "printk" },
	{ 0x2e60bace, "memcpy" },
	{ 0x279bd6d2, "__nlmsg_put" },
	{ 0xb76ca35f, "__alloc_skb" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "AE1C8D198BE43F91AE9D1A9");
