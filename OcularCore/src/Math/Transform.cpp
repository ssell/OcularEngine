/**
 * Copyright 2014-2015 Steven T Sell (ssell@ocularinteractive.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Math/Transform.hpp"
#include "Math/Euler.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Math
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Transform::Transform(Vector3f const& position, Quaternion const& rotation, Vector3f const& scale)
            : m_Position(position), m_Rotation(rotation), m_Scale(scale)
        {
        
        }

        Transform::Transform()
        {

        }

        Transform::~Transform()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        void Transform::setPosition(Vector3f const& position)
        {
            m_Position = position;
        }

        Vector3f Transform::getPosition() const
        {
            return m_Position;
        }

        void Transform::setRotation(Quaternion const& rotation)
        {
            m_Rotation = rotation;
        }

        Quaternion Transform::getRotation() const
        {
            return m_Rotation;
        }

        void Transform::setScale(Vector3f const& scale)
        {
            m_Scale = scale;
        }

        Vector3f Transform::getScale() const
        {
            return m_Scale;
        }

        Vector3f Transform::getForwards() const
        {
            return m_Rotation.getZRotationAxis();
        }

        Vector3f Transform::getUp() const
        {
            return m_Rotation.getYRotationAxis();
        }

        Vector3f Transform::getRight() const
        {
            return m_Rotation.getXRotationAxis();
        }

        void Transform::translate(Vector3f const& translation)
        {
            m_Position += translation;
        }

        void Transform::moveForward(float const delta)
        {
            translate(getForwards() * delta);
        }

        void Transform::moveUp(float const delta)
        {
            translate(getUp() * delta);
        }

        void Transform::moveRight(float const delta)
        {
            translate(getRight() * delta);
        }

        void Transform::rotate(Vector3f const& axis, float const angle)
        {
            m_Rotation = Quaternion(axis, angle);
        }

        void Transform::lookAt(Vector3f const& point, Vector3f const& upVector)
        {
            m_Rotation = Quaternion::CreateLookAtRotation(m_Position, point, upVector);
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}