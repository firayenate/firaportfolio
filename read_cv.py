from docx import Document

def read_docx(file_path):
    doc = Document(file_path)
    for i, para in enumerate(doc.paragraphs):
        if para.text.strip():
            print(f"[{i}] {para.text}")

if __name__ == "__main__":
    read_docx("Firaol_Desalegn_CV.docx")
