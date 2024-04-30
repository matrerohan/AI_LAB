# %%
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Conv2D, MaxPooling2D, Dense, Flatten, Dropout

# %%
train_datagen = ImageDataGenerator(rescale=1./255)
test_datagen = ImageDataGenerator(rescale=1./255)

# %%
train_generator = train_datagen.flow_from_directory(
    './train',
    target_size=(256, 256),
    batch_size=32,
    class_mode='categorical')

# %%
test_generator = test_datagen.flow_from_directory(
    './test',
    target_size=(256, 256),
    batch_size=32,
    class_mode='categorical')

# %%
model = Sequential([
    Conv2D(32, (3, 3), activation='relu', input_shape=(256, 256, 3)),
    MaxPooling2D(2, 2),
    Conv2D(64, (3, 3), activation='relu'),
    MaxPooling2D(2, 2),
    Conv2D(128, (3, 3), activation='relu'),
    MaxPooling2D(2, 2),
    Flatten(),
    Dense(128, activation='relu'),
    Dense(3, activation='softmax')
])

# %%
model.compile(
    optimizer='adam',
    loss='categorical_crossentropy',
    metrics=['accuracy'])

# %%
model.fit(
      train_generator,
      steps_per_epoch=1,
      epochs=10,
      validation_data=test_generator,
      validation_steps=1)

# %%
import math

test_loss, test_acc = model.evaluate(test_generator, steps=math.ceil(test_generator.samples / 32))
print('Test accuracy:', test_acc)


