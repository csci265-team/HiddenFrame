import { ButtonHTMLAttributes } from "react";

interface ButtonProps extends ButtonHTMLAttributes<HTMLButtonElement> { }

export const Button: React.FC<ButtonProps> = (props) => {
    return (
        <button
            className={`p-2 bg-colors-hf-brown text-colors-hf-beige dark:bg-colors-hf-beige dark:text-colors-hf-brown rounded-lg`}
            {...props} />
    );
}