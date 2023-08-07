from pathlib import Path

def extract_last_directory_with_filename(directory_path):
    directory_path = Path(directory_path)
    
    if directory_path.is_dir():    
        for file_path in directory_path.iterdir():
            if file_path.is_file():
                resourcePath = str(directory_path).replace("\\", "/") + "/" + file_path.name
                resourceID = f"{directory_path.name}_{file_path.stem}"
                print(f"{resourcePath}, {resourceID}")


def filename(directory_path):
    directory_path = Path(directory_path)
    
    if directory_path.is_dir():    
        for file_path in directory_path.iterdir():
            resourcePath = str(directory_path).replace("\\", "/") + "/" + file_path.name
            resourceID = file_path.stem
            print(f"{resourcePath}, {resourceID}")

