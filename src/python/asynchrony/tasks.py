import asyncio
import time


async def example_task():
    print("example task")
    await asyncio.sleep(1)


async def task_generator():
    for i in range(5):
        asyncio.ensure_future(example_task())
    pending = asyncio.all_tasks()
    for p in pending:
        print(p)


loop = asyncio.get_event_loop()
loop.run_until_complete(task_generator())
loop.close()

print("The End")
