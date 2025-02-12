#include "../WorldObject.h"

FixedAttachment::FixedAttachment(std::string modelPath, std::string objectID, glm::vec3 pos, float rotation, bool visable, glm::vec3 scale)
{
	FixedAttachment::model = Model(modelPath);
	FixedAttachment::objectID = objectID;
	FixedAttachment::position = pos;
	FixedAttachment::rotation = rotation;
	FixedAttachment::visableToRender = visable;
	FixedAttachment::scaling = scale;
	FixedAttachment::derivedClassID = "FixedAttachment";
}

void FixedAttachment::buttonInteract(int button) {
	if (button == GLFW_KEY_R) {
		if (FixedAttachment::working == true) {
			FixedAttachment::position += glm::vec3(0.0f, 0.2f, 0.0f);
			std::cout << "adsf\n";
		}
		else {
			FixedAttachment::position += glm::vec3(0.0f, -0.2f, 0.0f);
		}
	}
}