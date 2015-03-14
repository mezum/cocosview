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

#ifndef cocosview_CCVDefaultScrollInertia_h
#define cocosview_CCVDefaultScrollInertia_h

#include "CCVMacros.h"
#include "CCVScrollInertia.h"

NS_CCV_BEG
class DefaultScrollInertia : public ScrollInertia
{
	public:
		/** the threathold to start to move. */
		float getStaticFriction() const { return _staticFriction; }
		void setStaticFriction(float value) { _staticFriction = value; }
	
		/** the coefficient of dynamic friction */
		float getDynamicFriction() const { return _dynamicFriction; }
		void setDynamicFriction(float value) { _dynamicFriction = value; }
	
		/** the coefficient of drag attenuation when the position has reached the edge of boundary. */
		float getEdgeAttenuation() const { return _edgeAttenuation; }
		void setEdgeAttenuation(float value) { _edgeAttenuation = value; }
	
		/** the cofficient of bringing back force when the position has reached the edge of boundary. */
		float getPullBackRate() const { return _pullBackRate; }
		void setPullBackRate(float rate) { _pullBackRate = rate; }
	
		void touch() override;
		void release() override;
		void drag(float amount) override;
		void moveTo(float value) override;
		void update(float delta) override;
	
	private:
		float _staticFriction = 5.0f;
		float _dynamicFriction = 0.90625f;
		float _edgeAttenuation = 0.375f;
		float _pullBackRate = 0.05f;
	
		bool _isTouching = false;
		float _velocity = 0.0f;
		float _prevVelocity = 0.0f;
		float _movement = 0.0f;
	
};
NS_CCV_END

#endif
