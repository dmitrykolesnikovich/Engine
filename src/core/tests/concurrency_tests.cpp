#include "core/concurrency.h"

#include "catch.hpp"

TEST_CASE("concurrency-tests-atomic-inc")
{
	SECTION("relaxed")
	{
		volatile i32 i32Test = 0;
		volatile i64 i64Test = 0;

		REQUIRE(AtomicInc(&i32Test) == 1);
		REQUIRE(i32Test == 1);

		REQUIRE(AtomicInc(&i64Test) == 1);
		REQUIRE(i64Test == 1);
	}
	SECTION("acq")
	{
		volatile i32 i32Test = 0;
		volatile i64 i64Test = 0;

		REQUIRE(AtomicIncAcq(&i32Test) == 1);
		REQUIRE(i32Test == 1);

		REQUIRE(AtomicIncAcq(&i64Test) == 1);
		REQUIRE(i64Test == 1);
	}
	SECTION("rel")
	{
		volatile i32 i32Test = 0;
		volatile i64 i64Test = 0;

		REQUIRE(AtomicIncRel(&i32Test) == 1);
		REQUIRE(i32Test == 1);

		REQUIRE(AtomicIncRel(&i64Test) == 1);
		REQUIRE(i64Test == 1);
	}
}


TEST_CASE("concurrency-tests-atomic-dec")
{
	SECTION("relaxed")
	{
		volatile i32 i32Test = 0;
		volatile i64 i64Test = 0;

		REQUIRE(AtomicDec(&i32Test) == -1);
		REQUIRE(i32Test == -1);

		REQUIRE(AtomicDec(&i64Test) == -1);
		REQUIRE(i64Test == -1);
	}
	SECTION("acq")
	{
		volatile i32 i32Test = 0;
		volatile i64 i64Test = 0;

		REQUIRE(AtomicDecAcq(&i32Test) == -1);
		REQUIRE(i32Test == -1);

		REQUIRE(AtomicDecAcq(&i64Test) == -1);
		REQUIRE(i64Test == -1);
	}
	SECTION("rel")
	{
		volatile i32 i32Test = 0;
		volatile i64 i64Test = 0;

		REQUIRE(AtomicDecRel(&i32Test) == -1);
		REQUIRE(i32Test == -1);

		REQUIRE(AtomicDecRel(&i64Test) == -1);
		REQUIRE(i64Test == -1);
	}
}

TEST_CASE("concurrency-tests-atomic-add")
{
	SECTION("relaxed")
	{
		volatile i32 i32Test = 0;
		volatile i64 i64Test = 0;

		REQUIRE(AtomicAdd(&i32Test, 8) == 8);
		REQUIRE(i32Test == 8);
		REQUIRE(AtomicAdd(&i32Test, -16) == -8);
		REQUIRE(i32Test == -8);

		REQUIRE(AtomicAdd(&i64Test, 8) == 8);
		REQUIRE(i64Test == 8);
		REQUIRE(AtomicAdd(&i64Test, -16) == -8);
		REQUIRE(i64Test == -8);
	}
	SECTION("acq")
	{
		volatile i32 i32Test = 0;
		volatile i64 i64Test = 0;

		REQUIRE(AtomicAddAcq(&i32Test, 8) == 8);
		REQUIRE(i32Test == 8);
		REQUIRE(AtomicAddAcq(&i32Test, -16) == -8);
		REQUIRE(i32Test == -8);

		REQUIRE(AtomicAddAcq(&i64Test, 8) == 8);
		REQUIRE(i64Test == 8);
		REQUIRE(AtomicAddAcq(&i64Test, -16) == -8);
		REQUIRE(i64Test == -8);
	}
	SECTION("rel")
	{
		volatile i32 i32Test = 0;
		volatile i64 i64Test = 0;

		REQUIRE(AtomicAddRel(&i32Test, 8) == 8);
		REQUIRE(i32Test == 8);
		REQUIRE(AtomicAddRel(&i32Test, -16) == -8);
		REQUIRE(i32Test == -8);

		REQUIRE(AtomicAddRel(&i64Test, 8) == 8);
		REQUIRE(i64Test == 8);
		REQUIRE(AtomicAddRel(&i64Test, -16) == -8);
		REQUIRE(i64Test == -8);
	}
}

TEST_CASE("concurrency-tests-atomic-and")
{
	SECTION("relaxed")
	{
		volatile i32 i32Test = 0xffff0000;
		volatile i64 i64Test = 0xffffffff00000000LL;

		REQUIRE(AtomicAnd(&i32Test, 0x00ffff00) == 0xffff0000);
		REQUIRE(i32Test == 0x00ff0000);

		REQUIRE(AtomicAnd(&i64Test, 0x0000ffffffff0000LL) == 0xffffffff00000000LL);
		REQUIRE(i64Test == 0x0000ffff00000000LL);
	}
	SECTION("acq")
	{
		volatile i32 i32Test = 0xffff0000;
		volatile i64 i64Test = 0xffffffff00000000LL;

		REQUIRE(AtomicAndAcq(&i32Test, 0x00ffff00) == 0xffff0000);
		REQUIRE(i32Test == 0x00ff0000);

		REQUIRE(AtomicAndAcq(&i64Test, 0x0000ffffffff0000LL) == 0xffffffff00000000LL);
		REQUIRE(i64Test == 0x0000ffff00000000LL);
	}
	SECTION("rel")
	{
		volatile i32 i32Test = 0xffff0000;
		volatile i64 i64Test = 0xffffffff00000000LL;

		REQUIRE(AtomicAndRel(&i32Test, 0x00ffff00) == 0xffff0000);
		REQUIRE(i32Test == 0x00ff0000);

		REQUIRE(AtomicAndRel(&i64Test, 0x0000ffffffff0000LL) == 0xffffffff00000000LL);
		REQUIRE(i64Test == 0x0000ffff00000000LL);
	}
}

TEST_CASE("concurrency-tests-atomic-or")
{
	SECTION("relaxed")
	{
		volatile i32 i32Test = 0xffff0000;
		volatile i64 i64Test = 0xffffffff00000000LL;

		REQUIRE(AtomicOr(&i32Test, 0x0000ffff) == 0xffff0000);
		REQUIRE(i32Test == 0xffffffff);

		REQUIRE(AtomicOr(&i64Test, 0x000000000ffffffffLL) == 0xffffffff00000000LL);
		REQUIRE(i64Test == 0xffffffffffffffffLL);
	}
	SECTION("acq")
	{
		volatile i32 i32Test = 0xffff0000;
		volatile i64 i64Test = 0xffffffff00000000LL;

		REQUIRE(AtomicOrAcq(&i32Test, 0x0000ffff) == 0xffff0000);
		REQUIRE(i32Test == 0xffffffff);

		REQUIRE(AtomicOrAcq(&i64Test, 0x000000000ffffffffLL) == 0xffffffff00000000LL);
		REQUIRE(i64Test == 0xffffffffffffffffLL);
	}
	SECTION("rel")
	{
		volatile i32 i32Test = 0xffff0000;
		volatile i64 i64Test = 0xffffffff00000000LL;

		REQUIRE(AtomicOrRel(&i32Test, 0x0000ffff) == 0xffff0000);
		REQUIRE(i32Test == 0xffffffff);

		REQUIRE(AtomicOrRel(&i64Test, 0x000000000ffffffffLL) == 0xffffffff00000000LL);
		REQUIRE(i64Test == 0xffffffffffffffffLL);
	}
}

TEST_CASE("concurrency-tests-atomic-xor")
{
	SECTION("relaxed")
	{
		volatile i32 i32Test = 0xffff0000;
		volatile i64 i64Test = 0xffffffff00000000LL;

		REQUIRE(AtomicXor(&i32Test, 0xffffffff) == 0xffff0000);
		REQUIRE(i32Test == 0x0000ffff);

		REQUIRE(AtomicXor(&i64Test, 0xffffffffffffffffLL) == 0xffffffff00000000LL);
		REQUIRE(i64Test == 0x00000000ffffffffLL);
	}
	SECTION("acq")
	{
		volatile i32 i32Test = 0xffff0000;
		volatile i64 i64Test = 0xffffffff00000000LL;

		REQUIRE(AtomicXorAcq(&i32Test, 0xffffffff) == 0xffff0000);
		REQUIRE(i32Test == 0x0000ffff);

		REQUIRE(AtomicXorAcq(&i64Test, 0xffffffffffffffffLL) == 0xffffffff00000000LL);
		REQUIRE(i64Test == 0x00000000ffffffffLL);
	}
	SECTION("rel")
	{
		volatile i32 i32Test = 0xffff0000;
		volatile i64 i64Test = 0xffffffff00000000LL;

		REQUIRE(AtomicXorRel(&i32Test, 0xffffffff) == 0xffff0000);
		REQUIRE(i32Test == 0x0000ffff);

		REQUIRE(AtomicXorRel(&i64Test, 0xffffffffffffffffLL) == 0xffffffff00000000LL);
		REQUIRE(i64Test == 0x00000000ffffffffLL);
	}
}

TEST_CASE("concurrency-tests-atomic-cmpexhg")
{
	SECTION("relaxed")
	{
		volatile i32 i32Test = 0;
		volatile i64 i64Test = 0;

		REQUIRE(AtomicCmpExchg(&i32Test, 1, 0) == 0);
		REQUIRE(i32Test == 1);
		REQUIRE(AtomicCmpExchg(&i32Test, 1, 0) == 1);
		REQUIRE(i32Test == 1);
		REQUIRE(AtomicCmpExchg(&i32Test, 2, 1) == 1);
		REQUIRE(i32Test == 2);

		REQUIRE(AtomicCmpExchg(&i64Test, 1, 0) == 0);
		REQUIRE(i64Test == 1);
		REQUIRE(AtomicCmpExchg(&i64Test, 1, 0) == 1);
		REQUIRE(i64Test == 1);
		REQUIRE(AtomicCmpExchg(&i64Test, 2, 1) == 1);
		REQUIRE(i64Test == 2);
	}
	SECTION("acq")
	{
		volatile i32 i32Test = 0;
		volatile i64 i64Test = 0;

		REQUIRE(AtomicCmpExchgAcq(&i32Test, 1, 0) == 0);
		REQUIRE(i32Test == 1);
		REQUIRE(AtomicCmpExchgAcq(&i32Test, 1, 0) == 1);
		REQUIRE(i32Test == 1);
		REQUIRE(AtomicCmpExchgAcq(&i32Test, 2, 1) == 1);
		REQUIRE(i32Test == 2);

		REQUIRE(AtomicCmpExchgAcq(&i64Test, 1, 0) == 0);
		REQUIRE(i64Test == 1);
		REQUIRE(AtomicCmpExchgAcq(&i64Test, 1, 0) == 1);
		REQUIRE(i64Test == 1);
		REQUIRE(AtomicCmpExchgAcq(&i64Test, 2, 1) == 1);
		REQUIRE(i64Test == 2);
	}
	SECTION("rel")
	{
		volatile i32 i32Test = 0;
		volatile i64 i64Test = 0;

		REQUIRE(AtomicCmpExchgRel(&i32Test, 1, 0) == 0);
		REQUIRE(i32Test == 1);
		REQUIRE(AtomicCmpExchgRel(&i32Test, 1, 0) == 1);
		REQUIRE(i32Test == 1);
		REQUIRE(AtomicCmpExchgRel(&i32Test, 2, 1) == 1);
		REQUIRE(i32Test == 2);

		REQUIRE(AtomicCmpExchgRel(&i64Test, 1, 0) == 0);
		REQUIRE(i64Test == 1);
		REQUIRE(AtomicCmpExchgRel(&i64Test, 1, 0) == 1);
		REQUIRE(i64Test == 1);
		REQUIRE(AtomicCmpExchgRel(&i64Test, 2, 1) == 1);
		REQUIRE(i64Test == 2);
	}
}

TEST_CASE("concurrency-tests-thread")
{
	SECTION("invalid")
	{
		Thread thread;
		REQUIRE(!thread);
	}

	SECTION("create")
	{
		volatile i32 value = 1;
		Thread thread(
		    [](void* userData) -> int {
			    AtomicDec((volatile i32*)userData);
			    return 123;
		    },
		    (void*)&value);
		REQUIRE(thread);
		int retVal = thread.Join();
		REQUIRE(retVal == 123);
		REQUIRE(!thread);
		REQUIRE(value == 0);
	}

	SECTION("move")
	{
		volatile i32 value = 1;
		Thread thread(
		    [](void* userData) -> int {
			    AtomicDec((volatile i32*)userData);
			    return 123;
		    },
		    (void*)&value);
		REQUIRE(thread);

		Thread thread2;
		REQUIRE(!thread2);
		thread2 = std::move(thread);
		REQUIRE(!thread);
		REQUIRE(thread2);
		int retVal = thread2.Join();
		REQUIRE(retVal == 123);
		REQUIRE(!thread2);
		REQUIRE(value == 0);
	}
}

TEST_CASE("concurrency-tests-event")
{
	SECTION("st-default")
	{
		Event event(false, false);
		REQUIRE(!event.Wait(1));
		REQUIRE(!event.Wait(10));
		REQUIRE(event.Signal());
		REQUIRE(event.Wait(-1));
		REQUIRE(!event.Wait(1));
		REQUIRE(!event.Wait(10));
	}

	SECTION("st-manual-reset")
	{
		Event event(true, false);
		REQUIRE(event.Signal());
		REQUIRE(event.Wait(-1));
		REQUIRE(event.Wait(1));
		REQUIRE(event.Wait(10));
		REQUIRE(event.Reset());
		REQUIRE(!event.Wait(1));
		REQUIRE(!event.Wait(10));
	}

	SECTION("st-manual-reset-start-signalled")
	{
		Event event(true, true);

		REQUIRE(event.Wait(-1));
		REQUIRE(event.Wait(1));
		REQUIRE(event.Wait(10));
		REQUIRE(event.Reset());
		REQUIRE(!event.Wait(1));
		REQUIRE(!event.Wait(10));
		REQUIRE(event.Signal());
		REQUIRE(event.Wait(-1));
		REQUIRE(event.Wait(1));
		REQUIRE(event.Wait(10));
		REQUIRE(event.Reset());
		REQUIRE(!event.Wait(1));
		REQUIRE(!event.Wait(10));
	}


	SECTION("mt-default")
	{
		Event event(false, false);
		REQUIRE(!event.Wait(1));
		REQUIRE(!event.Wait(10));
		Thread thread(
		    [](void* userData) -> int {
			    auto* event = (Event*)userData;
			    return event->Signal() ? 1 : 0;
		    },
		    (void*)&event);
		REQUIRE(event.Wait(-1));
		REQUIRE(thread.Join());
		REQUIRE(!event.Wait(1));
		REQUIRE(!event.Wait(10));
	}

	SECTION("mt-manual-reset")
	{
		Event event(true, false);
		Thread thread(
		    [](void* userData) -> int {
			    auto* event = (Event*)userData;
			    return event->Signal() ? 1 : 0;
		    },
		    (void*)&event);
		REQUIRE(event.Wait(-1));
		REQUIRE(thread.Join());
		REQUIRE(event.Wait(1));
		REQUIRE(event.Wait(10));
		REQUIRE(event.Reset());
		REQUIRE(!event.Wait(1));
		REQUIRE(!event.Wait(10));
	}

	SECTION("mt-manual-reset-start-signalled")
	{
		Event event(true, true);

		REQUIRE(event.Wait(-1));
		REQUIRE(event.Wait(1));
		REQUIRE(event.Wait(10));
		REQUIRE(event.Reset());
		REQUIRE(!event.Wait(1));
		REQUIRE(!event.Wait(10));
		Thread thread(
		    [](void* userData) -> int {
			    auto* event = (Event*)userData;
			    return event->Signal() ? 1 : 0;
		    },
		    (void*)&event);
		REQUIRE(event.Wait(-1));
		REQUIRE(thread.Join());
		REQUIRE(event.Wait(1));
		REQUIRE(event.Wait(10));
		REQUIRE(event.Reset());
		REQUIRE(!event.Wait(1));
		REQUIRE(!event.Wait(10));
	}
}

TEST_CASE("concurrency-tests-mutex")
{
	SECTION("recursive")
	{
		Mutex mutex;

		mutex.Lock();
		REQUIRE(mutex.TryLock());
		mutex.Unlock();
		mutex.Unlock();
	}
}