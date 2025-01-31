-- Add new columns to sales table
ALTER TABLE sales ADD COLUMN customer_name TEXT;
ALTER TABLE sales ADD COLUMN amount_paid REAL;
ALTER TABLE sales ADD COLUMN change_amount REAL; 