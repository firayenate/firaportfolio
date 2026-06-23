from docx import Document

def add_portfolio_link(file_path):
    doc = Document(file_path)
    
    # Find the paragraph with GitHub and add portfolio after it
    for i, para in enumerate(doc.paragraphs):
        if "github.com/firayenate" in para.text.lower() or "github:" in para.text.lower():
            # Insert portfolio link after GitHub
            para.text = "GitHub: https://github.com/firayenate"
            # Add portfolio on next line by modifying the next paragraph or adding new
            break
    
    # Add portfolio link
    doc.add_paragraph("Portfolio: https://firayenate.github.io/firaportfolio")
    
    doc.save(file_path)
    print("Portfolio link added to CV!")

if __name__ == "__main__":
    add_portfolio_link("Firaol_Desalegn_CV.docx")
