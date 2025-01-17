/* Transceiver52M/radioClock.cpp */
/*-
 * Written by Thomas Tsou <ttsou@vt.edu>
 * Based on code by Harvind S Samra <hssamra@kestrelsp.com>
 *
 * Copyright 2011 Free Software Foundation, Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * See the COPYING file in the main directory for details.
 */

#include "radioClock.h"

void RadioClock::set(const GSM::Time &wTime)
{
	mLock.lock();
	mClock = wTime;
	updateSignal.signal();
	mLock.unlock();
}

void RadioClock::incTN()
{
	mLock.lock();
	mClock.incTN();
	updateSignal.signal();
	mLock.unlock();
}

GSM::Time RadioClock::get()
{
	mLock.lock();
	GSM::Time retVal = mClock;
	mLock.unlock();

	return retVal;
}

void RadioClock::wait()
{
	mLock.lock();
	updateSignal.wait(mLock, 1);
	mLock.unlock();
}
