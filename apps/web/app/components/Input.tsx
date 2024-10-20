import { InputHTMLAttributes } from "react";

interface InputProps extends InputHTMLAttributes<HTMLInputElement> { }

export const Input: React.FC<InputProps> = (props) => {
    return (
        <input
            className={`p-2 border-2 bg-transparent border-colors-hf-brown dark:border-colors-hf-beige rounded-lg placeholder:text-colors-hf-brown/60 dark:placeholder:text-colors-hf-beige/60`}
            {...props} />
    );
};