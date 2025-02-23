/*
 * Xournal++
 *
 * A TexImage on the document
 *
 * @author Xournal++ Team
 * https://github.com/xournalpp/xournalpp
 *
 * @license GNU GPLv2 or later
 */

#pragma once

#include <memory>
#include <string>
#include <vector>

#include <poppler.h>

#include "Element.h"


class TexImage: public Element {
public:
    TexImage();
    TexImage(const TexImage&) = delete;
    TexImage& operator=(const TexImage&) = delete;
    TexImage(const TexImage&&) = delete;
    TexImage&& operator=(const TexImage&&) = delete;
    virtual ~TexImage();

public:
    void setWidth(double width);
    void setHeight(double height);

    /**
     * Returns the binary data (PDF or PNG (deprecated)).
     */
    const std::string& getBinaryData() const;

    /**
     * @return The image, if render source is PNG. Note: this is deprecated.
     */
    cairo_surface_t* getImage() const;

    /**
     * @return The PDF Document, if rendered as a PDF.
     *
     * The document needs to be referenced, if it will be hold somewhere
     */
    PopplerDocument* getPdf() const;

    virtual void scale(double x0, double y0, double fx, double fy, double rotation, bool restoreLineWidth);
    virtual void rotate(double x0, double y0, double th);

    // text tag to alow latex
    void setText(std::string text);
    std::string getText() const;

    virtual Element* clone();

    /**
     * @return true if the binary data (PNG or PDF) was loaded successfully.
     */
    bool loadData(std::string&& bytes, GError** err = nullptr);

public:
    // Serialize interface
    void serialize(ObjectOutputStream& out);
    void readSerialized(ObjectInputStream& in);

private:
    void calcSize() const override;

    static cairo_status_t cairoReadFunction(TexImage* image, unsigned char* data, unsigned int length);

    /**
     * Free image and PDF
     */
    void freeImageAndPdf();

private:
    /**
     * Tex PDF Document, if rendered as PDF
     */
    PopplerDocument* pdf = nullptr;

    /**
     * Tex image, if rendered as image. Note: this is deprecated and subject to removal in a later version.
     */
    cairo_surface_t* image = nullptr;

    /**
     * PNG Image / PDF Document
     */
    std::string binaryData;

    /**
     * Read position for PNG binaryData (deprecated).
     */
    std::string::size_type read = 0;

    /**
     * Tex String
     */
    std::string text;
};
