#include <assert.h>

// #define VK_CHECK(call)                                                         \
//   do {                                                                         \
//     VkResult result_ = call;                                                   \
//     assert(result_ == VK_SUCCESS);                                             \
//   } while (0)

// #define VK_CHECK_SWAPCHAIN(call)                                               \
//   do {                                                                         \
//     VkResult result_ = call;                                                   \
//     assert(result_ == VK_SUCCESS || result_ == VK_SUBOPTIMAL_KHR ||            \
//            result_ == VK_ERROR_OUT_OF_DATE_KHR);                               \
//   } while (0)