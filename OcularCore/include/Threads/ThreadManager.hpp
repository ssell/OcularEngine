#pragma once
#ifndef __H__OCULAR_CORE_THREAD_MANAGER__H__
#define __H__OCULAR_CORE_THREAD_MANAGER__H__

#include <future>
#include <thread>
#include <utility>
#include <vector>

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        /**
         * \class ThreadManager
         *
         * Primarily a wrapper around the C++ standard concurrency library.
         *
         * Async Example 1:
         *
         * Launch four asynchronous tasks, and wait for them all to complete manually.
         *
         *     auto func = [](uint32_t const index)->void { ... do something ... };
         *
         *     auto task0 = OcularThreads->spawnAsyncNow(func, 0);
         *     auto task1 = OcularThreads->spawnAsyncNow(func, 1);
         *     auto task2 = OcularThreads->spawnAsyncNow(func, 2);
         *     auto task3 = OcularThreads->spawnAsyncNow(func, 3);
         *
         *     task0.wait();
         *     task1.wait();
         *     task2.wait();
         *     task3.wait();
         *
         * Async Example 2:
         *
         * Launch four asynchronous tasks, and wait for them in a single call.
         *
         *     auto func = [](uint32_t const index){ ... do something ... };
         *
         *     OcularThreads->waitForAsyncs<void>(
         *         &OcularThreads->spawnAsyncNow(func, 0),
         *         &OcularThreads->spawnAsyncNow(func, 1),
         *         &OcularThreads->spawnAsyncNow(func, 2),
         *         &OcularThreads->spawnAsyncNow(func, 3));
         */

        class ThreadManager
        {
        public:

            ThreadManager();
            ~ThreadManager();

            /**
             * Spawns an asynchronous task.
             *
             * Depending on load, task may be created as deferred in which case
             * it will be executed synchronously.
             *
             * \param[in] function Function to execute
             * \param[in] args     Function parameters
             *
             * \return Future associated with the task. May be used to block until task completion
             *         or to retrieve any function return values.
             */
            /*template<typename F, typename ... Args>
            inline auto spawnAsync(F&& function, Args&& ... args) -> std::async<F, Args>
            {
                auto result = std::async(std::forward<F>(function), std::forward<Args>(args) ...);

                if (result.wait_for(0) == std::future_status::deferred)
                {
                    // Async task was created as deferred.
                    // Call wait on the future to force it's execution to begin.
                    result.wait();
                }

                return result;
            }*/

            /**
             * Spawns a truly asynchronous task.
             *
             * \param[in] function Function to execute
             * \param[in] args     Function parameters
             *
             * \return Future associated with the task. May be used to block until task completion
             *         or to retrieve any function return values.
             */
            /*template<typename F, typename ... Args>
            inline auto spawnAsyncNow(F&& function, Args&& ... args) -> std::async<F, Args>
            {
                return std::async(std::launch::async, std::forward<F>(function), std::forward<Args>(args) ...);
            }*/

            /**
             * Waits for all of the provided futures to finish. The futures must be of the same type.
             *
             * T template is the return value of the provided futures.
             *
             * \param[in] futures
             */
            /*template<typename T, typename ... F>
            inline void waitForAsyncs(F&& ... futures)
            {
                std::vector<std::future<T>*> futuresContainer = { futures ... };

                for (auto iter = futuresContainer.begin(); iter != futuresContainer.end(); ++iter)
                {
                    (*iter)->wait();
                }
            }*/

        protected:

        private:
        };
    }
}

//------------------------------------------------------------------------------------------

#endif