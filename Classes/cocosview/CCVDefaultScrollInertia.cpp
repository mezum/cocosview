/*
 Copyright (c) 2015 RyujuOrchestra.
 This software is released under the MIT License.
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/

#include "CCVDefaultScrollInertia.h"

static constexpr float TARGET_FRAME_DELTA_TIME = 1 / 60.0f;
static constexpr float MAX_FRAME_SKIP_SIZE = 3.0f;

NS_CCV_BEG

void DefaultScrollInertia::touch()
{
	_isTouching = true;
	_velocity = 0.0f;
	_prevVelocity = 0.0f;
	_movement = 0.0f;
}

void DefaultScrollInertia::release()
{
	_isTouching = false;
	_velocity = _prevVelocity;
	_movement = 0.0f;
}

void DefaultScrollInertia::drag(float amount)
{
	if (_isTouching) {
		_velocity += amount;
		_movement += (amount >= 0.0f ? amount : -amount);
	}
	else {
		setCurrent(getCurrent() + amount);
	}
}

void DefaultScrollInertia::moveTo(float value)
{
	setCurrent(value);
	_velocity = 0.0f;
	_prevVelocity = 0.0f;
}

void DefaultScrollInertia::update(float delta)
{
	if (_isTouching) {
		if (_movement >= _staticFriction) {
			if (getCurrent() < getMin() || getCurrent() > getMax()) {
				_velocity *= _edgeAttenuation;
			}
			setCurrent(getCurrent() + _velocity);
			_prevVelocity = _velocity;
			_velocity = 0.0f;
		}
		else {
			_prevVelocity = 0.0f;
		}
	}
	else {
		float fpsRate = delta / TARGET_FRAME_DELTA_TIME;
		if (fpsRate > MAX_FRAME_SKIP_SIZE) fpsRate = MAX_FRAME_SKIP_SIZE;
		
		if (getCurrent() < getMin()) {
			_prevVelocity = _velocity;
			_velocity = (getMin() - getCurrent()) * _pullBackRate * fpsRate;
			setCurrent(getCurrent() + _velocity * fpsRate);
		}
		else if (getCurrent() > getMax()) {
			_prevVelocity = _velocity;
			_velocity = (getMax() - getCurrent()) * _pullBackRate * fpsRate;
			setCurrent(getCurrent() + _velocity * fpsRate);
		}
		else if (_velocity >= 0.5f || _velocity <= -0.5f) {
			_prevVelocity = _velocity;
			_velocity *= _dynamicFriction * fpsRate;
			setCurrent(getCurrent() + _velocity * fpsRate);
		}
		else {
			_prevVelocity = _velocity;
			_velocity = 0.0f;
		}
	}
}

NS_CCV_END

