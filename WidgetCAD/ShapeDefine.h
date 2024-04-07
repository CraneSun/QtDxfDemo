#ifndef SHAPEDEFINE_H
#define SHAPEDEFINE_H

enum SHAPE_TYPE{
    SHAPE_LINE = 110,
    SHAPE_RECTANGLE,
    SHAPE_CIRCLE,
    SHAPE_DOT,
    SHAPE_POLYGAN
};


#define USERINFO_INDEX QGraphicsItem::UserType
#define USERINFO_SHAPE (QGraphicsItem::UserType+1)
#define USERINFO_UID (QGraphicsItem::UserType+2)

#endif // SHAPEDEFINE_H
