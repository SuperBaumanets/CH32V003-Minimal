#ifndef REG_ACCESS_H
#define REG_ACCESS_H

#define WRITE_REG(addr, val) \
    (*(volatile unsigned int *)(addr) = (unsigned int)(val))

#define READ_REG(addr) \
    (*(volatile unsigned int *)(addr))

#define WRITE_FIELD_REG(addr, field_mask, field_pos, field_val) \
    (*(volatile unsigned int *)(addr) = \
        (*(volatile unsigned int *)(addr) & ~((unsigned int)(field_mask) << (field_pos))) \
        | (((unsigned int)(field_val) << (field_pos)) \
           & ((unsigned int)(field_mask) << (field_pos))))

#define READ_FIELD_REG(addr, field_mask, field_pos) \
    ((*(volatile unsigned int *)(addr) & ((unsigned int)(field_mask) << (field_pos))) \
     >> (field_pos))

#endif /* REG_ACCESS_H */